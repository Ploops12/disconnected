#include "../View.h"
#include "../PhoneJack.h"
#include "raylib.h"
#include "raymath.h"

#define PHONE_JACK_LEAD_COLOR YELLOW

template<>
void View<PhoneJack>::draw() {
	Color jackColor{BLUE};
	if (data->color == 1) { jackColor = RED; }

	if (data->grabbed) {
		jackColor.r *= 0.85;
		jackColor.g *= 0.85;
		jackColor.b *= 0.85;
		DrawCircle(data->origin.x, data->origin.y, PHONE_JACK_RADIUS, jackColor);
	}

	// TODO: Make this draw a vector of segments
	View<CordSegment> cord_view(&data->cord);
	cord_view.draw();

	// If grabbed, do not render upright cable
	if (data->grabbed) { return; }

	Vector2 jackStart{(float)data->origin.x, (float)data->origin.y};
	Position endPos = data->getEnd();
	Vector2 jackEnd{(float)endPos.x, (float)endPos.y};

	Vector2 sheathEnd = Vector2MoveTowards(jackStart, jackEnd, (float)PHONE_JACK_SHEATH_LEN);
	float partialLeadLen = PhoneJack::getLength() - (PHONE_JACK_LEAD_LEN / 3);
	Vector2 leadEndPartial = Vector2MoveTowards(jackStart, jackEnd, partialLeadLen);

	DrawLineEx(jackStart, jackEnd, PHONE_JACK_LEAD_WIDTH / 2, PHONE_JACK_LEAD_COLOR);
	DrawLineEx(jackStart, leadEndPartial, PHONE_JACK_LEAD_WIDTH, PHONE_JACK_LEAD_COLOR);
	DrawLineEx(jackStart, sheathEnd, PHONE_JACK_SHEATH_WIDTH, jackColor);
}

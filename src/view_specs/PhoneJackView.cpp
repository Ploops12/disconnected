#include "../PhoneJack.h"
#include "../View.h"
#include "raylib.h"
#include "raymath.h"

#define PHONE_JACK_LEAD_COLOR YELLOW

void PhoneJack::draw() {
	Color jackColor{BLUE};
	if (color == 1) { jackColor = RED; }

	if (grabbed) {
		jackColor.r *= 0.85;
		jackColor.g *= 0.85;
		jackColor.b *= 0.85;
		DrawCircle(origin.x, origin.y, PHONE_JACK_RADIUS, jackColor);
	}

	// TODO: Make this draw a vector of segments
	cord.draw();

	// If grabbed, do not render upright cable
	if (grabbed) { return; }

	Vector2 jackStart{(float)origin.x, (float)origin.y};
	Position endPos = getEnd();
	Vector2 jackEnd{(float)endPos.x, (float)endPos.y};

	Vector2 sheathEnd = Vector2MoveTowards(jackStart, jackEnd, (float)PHONE_JACK_SHEATH_LEN);
	float partialLeadLen = PhoneJack::getLength() - (PHONE_JACK_LEAD_LEN / 3);
	Vector2 leadEndPartial = Vector2MoveTowards(jackStart, jackEnd, partialLeadLen);

	DrawLineEx(jackStart, jackEnd, PHONE_JACK_LEAD_WIDTH / 2, PHONE_JACK_LEAD_COLOR);
	DrawLineEx(jackStart, leadEndPartial, PHONE_JACK_LEAD_WIDTH, PHONE_JACK_LEAD_COLOR);
	DrawLineEx(jackStart, sheathEnd, PHONE_JACK_SHEATH_WIDTH, jackColor);
}

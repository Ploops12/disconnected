#include "../View.h"
#include "../CircuitSwitch.h"
#include "raylib.h"

constexpr int CIRCUIT_SWITCH_TRACK_PADDING {6};
constexpr int CIRCUIT_SWITCH_LINE_THICKNESS {2};

template<>
void View<CircuitSwitch>::draw() {
	int circleY = data->origin.y + (CIRCUIT_SWITCH_RADIUS / 2) + CIRCUIT_SWITCH_TRACK_PADDING;
	int centerX = data->origin.x + (CIRCUIT_SWITCH_TRACK_WIDTH / 2);

	if (data->state == SwitchState::MIDDLE) {
		circleY = data->origin.y + (CIRCUIT_SWITCH_TRACK_LEN / 2);
	} else if (data->state == SwitchState::BOTTOM) {
		circleY = data->origin.y + CIRCUIT_SWITCH_TRACK_LEN - (CIRCUIT_SWITCH_RADIUS / 2) - CIRCUIT_SWITCH_TRACK_PADDING;
	}

	DrawRectangleLines(data->origin.x, data->origin.y, CIRCUIT_SWITCH_TRACK_WIDTH, CIRCUIT_SWITCH_TRACK_LEN, DEFAULT_ELEMENT_COLOR);
	DrawLineEx({(float)centerX, (float)(data->origin.y + CIRCUIT_SWITCH_TRACK_PADDING)}, {(float)centerX, (float)(data->origin.y + CIRCUIT_SWITCH_TRACK_LEN - CIRCUIT_SWITCH_TRACK_PADDING)}, CIRCUIT_SWITCH_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	Color handleColor{BLUE};
	if (data->color == 1) { handleColor = RED; }

	DrawCircle(centerX, circleY, CIRCUIT_SWITCH_RADIUS, handleColor);
}


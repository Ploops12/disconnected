#include "../CircuitSwitch.h"
#include "../View.h"
#include "raylib.h"

constexpr int CIRCUIT_SWITCH_TRACK_PADDING {6};
constexpr int CIRCUIT_SWITCH_LINE_THICKNESS {2};

void CircuitSwitch::draw() {
	int circleY = origin.y + (CIRCUIT_SWITCH_RADIUS / 2) + CIRCUIT_SWITCH_TRACK_PADDING;
	int centerX = origin.x + (CIRCUIT_SWITCH_TRACK_WIDTH / 2);

	if (state == SwitchState::MIDDLE) {
		circleY = origin.y + (CIRCUIT_SWITCH_TRACK_LEN / 2);
	} else if (state == SwitchState::BOTTOM) {
		circleY = origin.y + CIRCUIT_SWITCH_TRACK_LEN - (CIRCUIT_SWITCH_RADIUS / 2) - CIRCUIT_SWITCH_TRACK_PADDING;
	}

	DrawRectangleLines(origin.x, origin.y, CIRCUIT_SWITCH_TRACK_WIDTH, CIRCUIT_SWITCH_TRACK_LEN, DEFAULT_ELEMENT_COLOR);
	DrawLineEx({(float)centerX, (float)(origin.y + CIRCUIT_SWITCH_TRACK_PADDING)}, {(float)centerX, (float)(origin.y + CIRCUIT_SWITCH_TRACK_LEN - CIRCUIT_SWITCH_TRACK_PADDING)}, CIRCUIT_SWITCH_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	Color handleColor{BLUE};
	if (color == 1) { handleColor = RED; }

	DrawCircle(centerX, circleY, CIRCUIT_SWITCH_RADIUS, handleColor);
}


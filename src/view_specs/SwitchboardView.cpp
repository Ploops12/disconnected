#include "../Switchboard.h"
#include "../View.h"
#include "raylib.h"

void Switchboard::draw() {
	float boxWidth = getVisualWidth();
	float boxHeight = getVisualHeight();

	Rectangle bounds{(float)origin.x, (float)origin.y, boxWidth, boxHeight};
	DrawRectangleLinesEx(bounds, BOX_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	for (auto& panel : panels) {
		panel.draw();
	}
}

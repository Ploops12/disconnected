#include "../ControlPanel.h"
#include "../View.h"
#include "raylib.h"

void ControlPanel::draw() {
	Rectangle bounds{(float)origin.x, (float)origin.y, (float)width, (float)getVisualHeight()};
	DrawRectangleLinesEx(bounds, BOX_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	for (auto& circuit : cordCircuits) {
		circuit.draw();
	}
}

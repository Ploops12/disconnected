#include "../SwitchingPanel.h"
#include "../View.h"
#include "raylib.h"

#include <iostream>

void SwitchingPanel::draw() {
	float xSize = getVisualWidth();
	float ySize = getVisualHeight();
	Rectangle bounds{(float)origin.x, (float)origin.y, xSize, ySize};
	DrawRectangleLinesEx(bounds, BOX_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	for (auto ext : extensions) {
		ext.draw();
	}
}

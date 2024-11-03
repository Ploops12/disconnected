#include "../NumberPlate.h"
#include "../View.h"
#include "raylib.h"

#include <string>

constexpr int NUMBER_PLATE_FONT_SIZE {1};

void NumberPlate::draw() {
	int adjCenterWidth = center.x - (NUMBER_PLATE_WIDTH / 2) + 1;
	int adjCenterHeight = center.y - (NUMBER_PLATE_HEIGHT / 2);

	DrawRectangleLines(adjCenterWidth, adjCenterHeight, NUMBER_PLATE_WIDTH, NUMBER_PLATE_HEIGHT, DEFAULT_ELEMENT_COLOR);

	std::string numberStr = std::to_string(number);
	int fontWidthAdj = ((NUMBER_PLATE_WIDTH - MeasureText(numberStr.c_str(), NUMBER_PLATE_FONT_SIZE)) / 2) - 1;
	DrawText(numberStr.c_str(), adjCenterWidth + fontWidthAdj, adjCenterHeight + 1, NUMBER_PLATE_FONT_SIZE, DEFAULT_ELEMENT_COLOR);
}

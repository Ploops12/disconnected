#include "../View.h"
#include "../NumberPlate.h"
#include "raylib.h"

#include <string>

constexpr int NUMBER_PLATE_FONT_SIZE {1};

template<>
void View<NumberPlate>::draw() {
	int adjCenterWidth = data->center.x - (NUMBER_PLATE_WIDTH / 2) + 1;
	int adjCenterHeight = data->center.y - (NUMBER_PLATE_HEIGHT / 2);

	DrawRectangleLines(adjCenterWidth, adjCenterHeight, NUMBER_PLATE_WIDTH, NUMBER_PLATE_HEIGHT, DEFAULT_ELEMENT_COLOR);

	std::string number = std::to_string(data->number);
	int fontWidthAdj = ((NUMBER_PLATE_WIDTH - MeasureText(number.c_str(), NUMBER_PLATE_FONT_SIZE)) / 2) - 1;
	DrawText(number.c_str(), adjCenterWidth + fontWidthAdj, adjCenterHeight + 1, NUMBER_PLATE_FONT_SIZE, DEFAULT_ELEMENT_COLOR);
}

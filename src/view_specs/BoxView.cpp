#include "../View.h"
#include "raylib.h"

constexpr int BOX_LINE_THICKNESS {2};

template<>
void View<Rectangle>::draw() {
	int adjX = data->x;// - (data->width / 2) + 1;
	int adjY = data->y;// - (data->height / 2);
	Rectangle newRec{(float)adjX, (float)adjY, data->width, data->height};
	DrawRectangleLinesEx(newRec, BOX_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);
}

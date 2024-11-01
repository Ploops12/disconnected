#include "../View.h"
#include "../CordSegment.h"
#include "raylib.h"

template<>
void View<CordSegment>::draw() {
	Color lineColor{BLUE};
	if (data->color == 1) {
		lineColor = RED;
	}

	Position startPos = data->getStart();
	Vector2 startPoint{(float)startPos.x, (float)startPos.y};
	Position endPos = data->getEnd();
	Vector2 endPoint{(float)endPos.x, (float)endPos.y};
	DrawLineEx(startPoint, endPoint, CORD_SEGMENT_WIDTH, lineColor);
}

#include "../CordSegment.h"
#include "../View.h"
#include "raylib.h"

void CordSegment::draw() {
	Color lineColor{BLUE};
	if (color == 1) {
		lineColor = RED;
	}

	Position startPos = getStart();
	Vector2 startPoint{(float)startPos.x, (float)startPos.y};
	Position endPos = getEnd();
	Vector2 endPoint{(float)endPos.x, (float)endPos.y};
	DrawLineEx(startPoint, endPoint, CORD_SEGMENT_WIDTH, lineColor);
}

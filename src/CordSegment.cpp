#include "CordSegment.h"
#include "raymath.h"

CordSegment::CordSegment(Position origin, int color, int length, float angle) : origin(origin), color(color), length(length), angle(angle)
{}

Position CordSegment::getEnd() {
	Vector2 startPoint{(float)origin.x, (float)origin.y};
	Vector2 moveDir = Vector2Subtract(startPoint, {startPoint.x, startPoint.y - length});
	moveDir = Vector2Rotate(moveDir, angle);
	Vector2 endPoint = Vector2Subtract(startPoint, moveDir);
	return {(int)endPoint.x, (int)(endPoint.y - 1)};
}

void CordSegment::shift(int x, int y) {
	origin.x += x;
	origin.y += y;
}

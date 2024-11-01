#include "PhoneJack.h"
#include "raylib.h"
#include "raymath.h"

PhoneJack::PhoneJack(Position origin, int color) : origin(origin), tetherPos(origin), color(color), cord(origin, color, 0) {}

Position PhoneJack::getEnd() {
	Vector2 startPoint{(float)origin.x, (float)origin.y};
	Vector2 moveDir = Vector2Subtract(startPoint, {startPoint.x, startPoint.y - getLength()});
	moveDir = Vector2Rotate(moveDir, angle);
	Vector2 endPoint = Vector2Subtract(startPoint, moveDir);
	return {(int)endPoint.x, (int)(endPoint.y - 1)};
}

void PhoneJack::move(int x, int y) {
	origin.x = x;
	origin.y = y;
	Vector2 startPoint{(float)origin.x, (float)origin.y};
	Vector2 tetherPoint{(float)tetherPos.x, (float)tetherPos.y};
	float distance = Vector2Distance(startPoint, tetherPoint);

	// TODO: Have this incrementally add new cords as they reach max length
	cord.length = (int)distance;
	cord.angle = -Vector2Angle(Vector2Subtract(tetherPoint, startPoint), {0,1});
}

void PhoneJack::shift(int x, int y) {
	origin.x += x;
	origin.y += y;
	tetherPos = origin;
	cord.shift(x, y);
}

bool PhoneJack::intersect(int x, int y) const {
	if (grabbed) {
		return CheckCollisionPointCircle({(float)x, (float)y}, {(float)origin.x, (float)origin.y}, PHONE_JACK_RADIUS);
	} else {
		Position boundsStart{origin.x - (PHONE_JACK_SHEATH_WIDTH / 2), origin.y - PHONE_JACK_SHEATH_LEN};
		if (x > boundsStart.x && y > boundsStart.y) {
			if (x < boundsStart.x + PHONE_JACK_SHEATH_WIDTH && y < boundsStart.y + PHONE_JACK_SHEATH_LEN) {
				return true;
			}
		}
	}

	return false;
}

void PhoneJack::setGrab(bool grab) {
	grabbed = grab;
}

void PhoneJack::setPort(Port port) {
	connectedPort = port;
}

Port PhoneJack::getPort() const {
	return connectedPort;
}

void PhoneJack::disconnect() {
	origin.x = tetherPos.x;
	origin.y = tetherPos.y;
	cord.length = 0;
	connectedPort.boardNum = -1;
	connectedPort.portNum = -1;
}

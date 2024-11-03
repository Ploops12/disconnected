#include "PhoneJack.h"
#include "Extension.h"
#include "raylib.h"
#include "raymath.h"

PhoneJack::PhoneJack(CordCircuit* circuit, Position origin, int color) : origin(origin), tetherPos(origin), color(color), cord(origin, color, 0), circuit(circuit) {}

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

void PhoneJack::disconnect() {
	origin.x = tetherPos.x;
	origin.y = tetherPos.y;
	cord.length = 0;
	grabbed = false;

	if (extension) {
		extension->disconnect();
		extension = nullptr;
	}
}

void PhoneJack::connect(Extension* ext) {
	if (extension) {
		extension->disconnect();
	}

	extension = ext;
	extension->connect(this);
	move(ext->getPortCenter().x, ext->getPortCenter().y);
}

void PhoneJack::grab() {
	grabbed = true;
}

const CordCircuit* PhoneJack::getCircuit() const {
	return circuit;
}

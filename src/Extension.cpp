#include "Extension.h"
#include "raylib.h"

Extension::Extension(int number, Position portCenter) :
	port{portCenter},
	label{number, {portCenter.x, portCenter.y - EXTENSION_ELEMENT_OFFSET}},
	light{{portCenter.x, portCenter.y + EXTENSION_ELEMENT_OFFSET}},
	number(number)
{}

void Extension::shift(int x, int y) {
	port.center.x += x;
	port.center.y += y;

	label.center.x += x;
	label.center.y += y;

	light.center.x += x;
	light.center.y += y;
}

bool Extension::intersect(int x, int y) const {
	return CheckCollisionPointCircle({(float)x, (float)y}, {(float)port.center.x, (float)port.center.y}, PHONE_PORT_RADIUS);
}

void Extension::disconnect() {
	jack = nullptr;
}

void Extension::insert(PhoneJack* jack) {
	this->jack = jack;
}

void Extension::setLight(bool state) {
	light.active = state;
}

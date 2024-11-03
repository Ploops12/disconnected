#include "../PhonePort.h"
#include "../View.h"
#include "raylib.h"

void PhonePort::draw() {
	DrawCircleLines(center.x, center.y, PHONE_PORT_RADIUS, DEFAULT_ELEMENT_COLOR);
}

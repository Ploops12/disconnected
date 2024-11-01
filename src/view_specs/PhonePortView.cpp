#include "../View.h"
#include "../PhonePort.h"
#include "raylib.h"

template<>
void View<PhonePort>::draw() {
	DrawCircleLines(data->center.x, data->center.y, PHONE_PORT_RADIUS, DEFAULT_ELEMENT_COLOR);
}

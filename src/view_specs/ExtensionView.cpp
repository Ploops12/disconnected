#include "../Extension.h"
#include "../View.h"
#include "raylib.h"

void Extension::draw() {
	port.draw();
	label.draw();
	light.draw();
}

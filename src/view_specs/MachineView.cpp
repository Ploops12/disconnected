#include "../Machine.h"
#include "../View.h"
#include "raylib.h"

void Machine::draw() {
	switchboard.draw();
	controls.draw();
}

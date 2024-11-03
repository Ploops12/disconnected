#include "../CordCircuit.h"
#include "../View.h"
#include "raylib.h"

void CordCircuit::draw() {
	Rectangle bounds{(float)(origin.x - (getVisualWidth() / 2)), (float)((origin.y + (PHONE_JACK_SHEATH_LEN / 2.5)) - (getVisualHeight() / 2)), (float)getVisualWidth(), (float)getVisualHeight()};
	DrawRectangleLinesEx(bounds, BOX_LINE_THICKNESS, DEFAULT_ELEMENT_COLOR);

	jack1.draw();
	jack2.draw();

	light1.draw();
	light2.draw();

	switch1.draw();
	switch2.draw();
}

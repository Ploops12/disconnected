#include "../View.h"
#include "../ControlPanel.h"
#include "raylib.h"

template<>
void View<ControlPanel>::draw() {
	Rectangle bounds{(float)data->origin.x, (float)data->origin.y, (float)data->width, (float)data->getVisualHeight()};
	View<Rectangle> bounds_view(&bounds);
	bounds_view.draw();

	for (auto& circuit : data->cordCircuits) {
		View<CordCircuit> circuit_view(&circuit);
		circuit_view.draw();
	}
}

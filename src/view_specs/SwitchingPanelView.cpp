#include "../View.h"
#include "../SwitchingPanel.h"
#include "raylib.h"

#include <iostream>

template<>
void View<SwitchingPanel>::draw() {
	float xSize = data->getVisualWidth();
	float ySize = data->getVisualHeight();
	Rectangle bounds{(float)data->origin.x, (float)data->origin.y, xSize, ySize};
	View<Rectangle> bounds_view(&bounds);
	bounds_view.draw();

	for (auto ext : data->extensions) {
		View<Extension> ext_view(&ext);
		ext_view.draw();
	}
}

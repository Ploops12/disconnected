#include "../View.h"
#include "../Switchboard.h"
#include "raylib.h"

template<>
void View<Switchboard>::draw() {
	float boxWidth = data->getVisualWidth();
	float boxHeight = data->getVisualHeight();

	Rectangle bounds{(float)data->origin.x, (float)data->origin.y, boxWidth, boxHeight};
	View<Rectangle> bounds_view(&bounds);
	bounds_view.draw();

	for (auto& panel : data->panels) {
		View<SwitchingPanel> panel_view(&panel);
		panel_view.draw();
	}
}

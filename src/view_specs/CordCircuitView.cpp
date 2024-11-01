#include "../View.h"
#include "../CordCircuit.h"
#include "raylib.h"

template<>
void View<CordCircuit>::draw() {
	Rectangle bounds{(float)(data->origin.x - (data->getVisualWidth() / 2)), (float)((data->origin.y + (PHONE_JACK_SHEATH_LEN / 2.5)) - (data->getVisualHeight() / 2)), (float)data->getVisualWidth(), (float)data->getVisualHeight()};
	View<Rectangle> bounds_view(&bounds);
	bounds_view.draw();

	View<PhoneJack> jack1_view(&data->jack1);
	View<PhoneJack> jack2_view(&data->jack2);
	jack1_view.draw();
	jack2_view.draw();

	View<IndicatorLight> light1_view(&data->light1);
	View<IndicatorLight> light2_view(&data->light2);
	light1_view.draw();
	light2_view.draw();

	View<CircuitSwitch> switch1_view(&data->switch1);
	View<CircuitSwitch> switch2_view(&data->switch2);
	switch1_view.draw();
	switch2_view.draw();
}

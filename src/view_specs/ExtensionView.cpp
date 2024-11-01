#include "../View.h"
#include "../Extension.h"
#include "raylib.h"

template<>
void View<Extension>::draw() {
	View<PhonePort> port_view(&data->port);
	View<NumberPlate> label_view(&data->label);
	View<IndicatorLight> light_view(&data->light);
	port_view.draw();
	label_view.draw();
	light_view.draw();
}

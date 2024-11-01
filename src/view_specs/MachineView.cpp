#include "../View.h"
#include "../Machine.h"
#include "raylib.h"

template<>
void View<Machine>::draw() {
	View<Switchboard> switchboard_view(&data->switchboard);
	View<ControlPanel> controls_view(&data->controls);
	switchboard_view.draw();
	controls_view.draw();
}

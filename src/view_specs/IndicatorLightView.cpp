#include "../View.h"
#include "../IndicatorLight.h"
#include "raylib.h"

#define INDICATOR_LIGHT_ON_COLOR YELLOW

template<>
void View<IndicatorLight>::draw() {
	DrawCircleLines(data->center.x, data->center.y, INDICATOR_LIGHT_RADIUS, DEFAULT_ELEMENT_COLOR);
	if (data->active) {
		DrawCircle(data->center.x, data->center.y, INDICATOR_LIGHT_RADIUS - 1, INDICATOR_LIGHT_ON_COLOR);
	}
}

#include "../IndicatorLight.h"
#include "../View.h"
#include "raylib.h"

#define INDICATOR_LIGHT_ON_COLOR YELLOW

void IndicatorLight::draw() {
	DrawCircleLines(center.x, center.y, INDICATOR_LIGHT_RADIUS, DEFAULT_ELEMENT_COLOR);
	if (active) {
		DrawCircle(center.x, center.y, INDICATOR_LIGHT_RADIUS - 1, INDICATOR_LIGHT_ON_COLOR);
	}
}

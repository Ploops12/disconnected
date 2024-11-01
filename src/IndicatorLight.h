#pragma once

#include "Position.h"

constexpr int INDICATOR_LIGHT_RADIUS {4};

struct IndicatorLight {
	Position center{0,0};
	bool active{false};
};

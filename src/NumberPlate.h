#pragma once

#include "Position.h"

constexpr int NUMBER_PLATE_WIDTH {20};
constexpr int NUMBER_PLATE_HEIGHT {10};

struct NumberPlate {
	int number;
	Position center;
};

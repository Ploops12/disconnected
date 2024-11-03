#pragma once

#include "Position.h"

constexpr int CORD_SEGMENT_MAX_LEN {12};
constexpr int CORD_SEGMENT_WIDTH {8};

class CordSegment {
public:
	CordSegment(Position origin, int color = 0, int length = CORD_SEGMENT_MAX_LEN, float angle = 0.0);
	Position getStart() { return origin; }
	Position getEnd();
	void shift(int x, int y);

	void draw();
	int length{0};
	float angle{0.0};

private:
	Position origin{0,0};
	// 0: BLUE | 1: RED
	int color{0};
};

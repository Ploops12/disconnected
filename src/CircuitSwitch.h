#pragma once

#include "Position.h"

constexpr int CIRCUIT_SWITCH_TRACK_WIDTH {13};
constexpr int CIRCUIT_SWITCH_TRACK_LEN {44};
constexpr int CIRCUIT_SWITCH_RADIUS {5};

enum class SwitchState {
	TOP = 1,
	MIDDLE = 0,
	BOTTOM = -1
};

struct SwitchSection {
	bool valid{false};
	SwitchState state{SwitchState::TOP};
};

struct CircuitSwitch {
	bool intersect(int x, int y) const;
	SwitchSection getSection(int x, int y) const;
	int color{0};
	Position origin{0,0};
	SwitchState state{SwitchState::MIDDLE};
	void draw();
};

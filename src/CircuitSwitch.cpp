#include "CircuitSwitch.h"

bool CircuitSwitch::intersect(int x, int y) const {
	if (x >= origin.x && y >= origin.y) {
		if (x <= origin.x + CIRCUIT_SWITCH_TRACK_WIDTH && y <= origin.y + CIRCUIT_SWITCH_TRACK_LEN) {
			return true;
		}
	}
	return false;
}

SwitchSection CircuitSwitch::getSection(int x, int y) const {
	SwitchSection section;

	int sectionDiv = CIRCUIT_SWITCH_TRACK_LEN / 3;
	if (intersect(x, y)) {
		int distance = y - origin.y;
		if (distance > sectionDiv * 2) {
			section.valid = true;
			section.state = SwitchState::BOTTOM;
		} else if (distance > sectionDiv) {
			section.valid = true;
			section.state = SwitchState::MIDDLE;
		} else {
			section.valid = true;
			section.state = SwitchState::TOP;
		}
	}

	return section;
}

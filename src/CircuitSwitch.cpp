#include "CircuitSwitch.h"

SwitchSection CircuitSwitch::intersect(int x, int y) const {
	SwitchSection section;

	int sectionDiv = CIRCUIT_SWITCH_TRACK_LEN / 3;
	if (x >= origin.x && y >= origin.y) {
		if (x <= origin.x + CIRCUIT_SWITCH_TRACK_WIDTH && y <= origin.y + CIRCUIT_SWITCH_TRACK_LEN) {
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
	}

	return section;
}

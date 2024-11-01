#include "CordCircuit.h"

constexpr int CORD_CIRCUIT_MIN_MARGIN {10};
constexpr int CORD_CIRCUIT_PADDING {10};

int getLargestWidth() {
	int largestWidth = PHONE_JACK_SHEATH_WIDTH;
	if (CIRCUIT_SWITCH_TRACK_WIDTH > largestWidth) {
		largestWidth = CIRCUIT_SWITCH_TRACK_WIDTH;
	} else if (INDICATOR_LIGHT_RADIUS * 2 > largestWidth) {
		largestWidth = INDICATOR_LIGHT_RADIUS * 2;
	}

	return largestWidth;
}

CordCircuit::CordCircuit(int id, Position origin) : id(id) {
	int margin = (getLargestWidth() + CORD_CIRCUIT_MIN_MARGIN) / 2;

	// Establish initial displacements
	jack1.shift(-margin, -(INDICATOR_LIGHT_RADIUS + CORD_CIRCUIT_MIN_MARGIN));
	jack2.shift(margin, -(INDICATOR_LIGHT_RADIUS + CORD_CIRCUIT_MIN_MARGIN));

	light1.center.x -= margin;
	light2.center.x += margin;

	switch1.origin.x -= CIRCUIT_SWITCH_TRACK_WIDTH + margin - (CIRCUIT_SWITCH_TRACK_WIDTH / 2) - 2;
	switch2.origin.x += margin - (CIRCUIT_SWITCH_TRACK_WIDTH / 2);
	switch1.origin.y += INDICATOR_LIGHT_RADIUS + CORD_CIRCUIT_MIN_MARGIN;
	switch2.origin.y += INDICATOR_LIGHT_RADIUS + CORD_CIRCUIT_MIN_MARGIN;

	move(origin.x, origin.y);
}

int CordCircuit::getVisualWidth() const {
	return getLargestWidth() + (CORD_CIRCUIT_PADDING * 2) + (CORD_CIRCUIT_MIN_MARGIN * 2);
}

int CordCircuit::getVisualHeight() const {
	return (INDICATOR_LIGHT_RADIUS * 2) + (CORD_CIRCUIT_MIN_MARGIN * 2) + (PHONE_JACK_SHEATH_LEN / 2) + CIRCUIT_SWITCH_TRACK_LEN + (CORD_CIRCUIT_PADDING * 2);
}

void CordCircuit::move(int x, int y) {
	int xShift = x - origin.x;
	int yShift = y - origin.y;

	origin.x = x;
	origin.y = y;

	jack1.shift(xShift, yShift);
	jack2.shift(xShift, yShift);

	light1.center.x += xShift;
	light1.center.y += yShift;
	light2.center.x += xShift;
	light2.center.y += yShift;

	switch1.origin.x += xShift;
	switch1.origin.y += yShift;
	switch2.origin.x += xShift;
	switch2.origin.y += yShift;
}

ControlType stateToType(bool left, SwitchState state) {
	switch(state) {
		case SwitchState::TOP:
			if (left) {
				return ControlType::SW1_T;
			} else {
				return ControlType::SW2_T;
			}

		case SwitchState::MIDDLE:
			if (left) {
				return ControlType::SW1_M;
			} else {
				return ControlType::SW2_M;
			}

		case SwitchState::BOTTOM:
			if (left) {
				return ControlType::SW1_B;
			} else {
				return ControlType::SW2_B;
			}
	}

	return ControlType::NONE;
}

ControlType CordCircuit::getControlClicked(int x, int y) const {
	if (jack1.intersect(x, y)) { return ControlType::JACK1; }
	else if (jack2.intersect(x, y)) { return ControlType::JACK2; }

	SwitchSection section = switch1.intersect(x, y);
	if (section.valid) { return stateToType(true, section.state); }

	section = switch2.intersect(x, y);
	if (section.valid) { return stateToType(false, section.state); }

	return ControlType::NONE;
}

void* CordCircuit::getControl(ControlType type) {
	switch(type) {
		case ControlType::LIGHT1:
			return &light1;
		case ControlType::LIGHT2:
			return &light2;
		case ControlType::JACK1:
			return &jack1;
		case ControlType::JACK2:
			return &jack2;
		case ControlType::SW1_T:
		case ControlType::SW1_M:
		case ControlType::SW1_B:
			return &switch1;
		case ControlType::SW2_T:
		case ControlType::SW2_M:
		case ControlType::SW2_B:
			return &switch2;
	}
	return nullptr;
}

const void* CordCircuit::getControl(ControlType type) const {
	switch(type) {
		case ControlType::LIGHT1:
			return &light1;
		case ControlType::LIGHT2:
			return &light2;
		case ControlType::JACK1:
			return &jack1;
		case ControlType::JACK2:
			return &jack2;
		case ControlType::SW1_T:
		case ControlType::SW1_M:
		case ControlType::SW1_B:
			return &switch1;
		case ControlType::SW2_T:
		case ControlType::SW2_M:
		case ControlType::SW2_B:
			return &switch2;
	}
	return nullptr;
}

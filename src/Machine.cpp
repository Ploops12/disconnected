#include "Machine.h"

Machine::Machine(int screenWidth, int screenHeight) {
	origin.x = (screenWidth / 2);
	origin.y = (screenHeight / 2);
}

bool Machine::addPanel(int rows, int cols) {
	bool retVal = switchboard.addPanel(rows, cols, 0);
	int shiftX = switchboard.getVisualWidth() / 2;
	int shiftY = (switchboard.getVisualHeight() + controls.getVisualHeight()) / 2;
	controls.setWidth(switchboard.getVisualWidth());
	move(origin.x - shiftX, origin.y - shiftY);
	return retVal;
}

bool Machine::addCordCircuit() {
	bool retVal = controls.addCordCircuit();
	return retVal;
}

void Machine::move(int x, int y) {
	switchboard.move(x, y);
	controls.move(x, y + switchboard.getVisualHeight() - 2);
}

Port Machine::getPortClicked(int x, int y) const {
	return switchboard.getPortClicked(x, y);
}

Control Machine::getControlClicked(int x, int y) const {
	return controls.getControlClicked(x, y);
}

Extension* Machine::getExtension(Port port) {
	return switchboard.getExtension(port);
}

const Extension* Machine::getExtension(Port port) const {
	return switchboard.getExtension(port);
}

ControlPtr Machine::getControl(Control control) {
	return controls.getControl(control);
}

const ConstControlPtr Machine::getControl(Control control) const {
	return controls.getControl(control);
}

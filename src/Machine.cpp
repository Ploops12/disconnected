#include "Machine.h"

Machine::Machine(int screenWidth, int screenHeight) {
	origin.x = (screenWidth / 2);
	origin.y = (screenHeight / 2);
}

bool Machine::addPanel(int rows, int cols) {
	bool retVal = switchboard.addPanel(rows, cols, 0);
	controls.setWidth(switchboard.getVisualWidth());
	recenter();
	return retVal;
}

bool Machine::addCordCircuit() {
	bool retVal = controls.addCordCircuit();
	return retVal;
}

void Machine::shift(int x, int y) {
	origin.x += x;
	origin.y += y;
	recenter();
}

void Machine::recenter() {
	int shiftX = switchboard.getVisualWidth() / 2;
	int shiftY = (switchboard.getVisualHeight() + controls.getVisualHeight()) / 2;
	switchboard.move(origin.x - shiftX, origin.y - shiftY);
	controls.move(origin.x - shiftX, origin.y - shiftY + switchboard.getVisualHeight() - 2);
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

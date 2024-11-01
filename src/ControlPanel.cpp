#include "ControlPanel.h"

constexpr int CONTROL_PANEL_PADDING {18};
constexpr int CONTROL_PANEL_MARGIN {10};
constexpr int MAGIC_NUM_HEIGHT_ADJ {3};

void ControlPanel::setWidth(int width) {
	this->width = width;
	recenter();
}

void ControlPanel::move(int x, int y) {
	origin.x = x;
	origin.y = y;
	recenter();
}

bool ControlPanel::addCordCircuit() {
	CordCircuit circuit(cordCircuits.size());
	int totalSize = getCircuitSize() + (CONTROL_PANEL_PADDING * 2);
	totalSize += CONTROL_PANEL_PADDING + circuit.getVisualWidth();

	if (totalSize > width) {
		return false;
	}

	cordCircuits.push_back(circuit);
	recenter();
	return true;
}

int ControlPanel::getVisualHeight() {
	if (cordCircuits.empty()) {
		CordCircuit circuit;
		return circuit.getVisualHeight() + (CONTROL_PANEL_PADDING * 2);
	} else {
		return cordCircuits.back().getVisualHeight() + (CONTROL_PANEL_PADDING * 2);
	}
}

Control ControlPanel::getControlClicked(int x, int y) const {
	Control control;
	for (int i = 0; i < cordCircuits.size(); i++) {
		ControlType type = cordCircuits[i].getControlClicked(x, y);
		if (type != ControlType::NONE) {
			control.type = type;
			control.cordCircuitId = i;
		}
	}
	return control;
}

ControlPtr ControlPanel::getControl(Control control) {
	ControlPtr controlPtr{nullptr, control.type};
	if (cordCircuits.size() > control.cordCircuitId) {
		controlPtr.ptr = cordCircuits[control.cordCircuitId].getControl(control.type);
	}
	return controlPtr;
}

const ConstControlPtr ControlPanel::getControl(Control control) const {
	const ConstControlPtr nullControl{nullptr, ControlType::NONE};
	if (cordCircuits.size() > control.cordCircuitId) {
		const void* ptr = cordCircuits[control.cordCircuitId].getControl(control.type);
		const ConstControlPtr controlPtr{ptr, control.type};
		return controlPtr;
	}
	return nullControl;
}

int ControlPanel::getCircuitSize() const {
	int totalSize{0};
	for (auto& circuit : cordCircuits) {
		totalSize += circuit.getVisualWidth() + CONTROL_PANEL_MARGIN;
	}

	// Don't count margin for final cord circuit
	return totalSize - CONTROL_PANEL_MARGIN;
}

void ControlPanel::recenter() {
	int totalSize = getCircuitSize();
	int sizeDiff = (width - totalSize) / 2;

	int index{0};
	for (auto& circuit : cordCircuits) {
		int shiftX = circuit.getVisualWidth() + CONTROL_PANEL_MARGIN;
		shiftX *= index + 0.5;
		// Account for the first element needing no margin on left
		shiftX -= CONTROL_PANEL_MARGIN / 2;
		circuit.move(origin.x + shiftX + sizeDiff, origin.y + (circuit.getVisualHeight() / 2) + (CONTROL_PANEL_PADDING / 2.5));
		++index;
	}
}

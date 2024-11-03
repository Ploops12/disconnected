#pragma once

#include "CordCircuit.h"

#include <vector>

struct Control {
	int cordCircuitId{-1};
	ControlType type{ControlType::NONE};
};

struct ControlPtr {
	void* ptr;
	ControlType type{ControlType::NONE};
};

struct ConstControlPtr {
	const void* ptr;
	ControlType type{ControlType::NONE};
};

class ControlPanel {
public:
	ControlPanel() = default;
	void setWidth(int width);
	void move(int x, int y);
	bool addCordCircuit();
	int getVisualHeight();

	Control getControlClicked(int x, int y) const;
	ControlPtr getControl(Control control);
	const ConstControlPtr getControl(Control control) const;

	void draw();

private:
	int getCircuitSize() const;
	void recenter();

	int width;
	Position origin;
	std::vector<CordCircuit> cordCircuits;
};

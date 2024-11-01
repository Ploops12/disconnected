#pragma once

#include "Switchboard.h"
#include "ControlPanel.h"
#include "View.h"

class Machine {
public:
	Machine(int screenWidth, int screenHeight);
	bool addPanel(int rows, int cols);
	bool addCordCircuit();

	int getVisualHeight();
	int getVisualWidth();

	Port getPortClicked(int x, int y) const;
	Control getControlClicked(int x, int y) const;

	Extension* getExtension(Port port);
	const Extension* getExtension(Port port) const;
	ControlPtr getControl(Control control);
	const ConstControlPtr getControl(Control control) const;

	friend void View<Machine>::draw();

private:
	void move(int x, int y);

	Position origin{0,0};
	Switchboard switchboard;
	ControlPanel controls;
};

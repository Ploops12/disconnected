#pragma once

#include "SwitchingPanel.h"
#include "Position.h"
#include "View.h"
#include "Port.h"

#include <vector>

class Switchboard {
public:
	Switchboard() = default;
	// Unlike the other positions, this is not a 2D position
	// It is the position in the array of panels in the switchboard
	bool addPanel(int rows, int cols, int position);
	void move(int x, int y);

	int getVisualWidth();
	int getVisualHeight();

	Port getPortClicked(int x, int y) const;
	Extension* getExtension(Port port);
	const Extension* getExtension(Port port) const;

	friend void View<Switchboard>::draw();

private:
	void recenter();
	Position origin{0,0};
	std::vector<SwitchingPanel> panels;
};

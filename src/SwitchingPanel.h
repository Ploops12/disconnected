#pragma once

#include "Extension.h"
#include "Position.h"
#include "View.h"

#include <vector>

constexpr int PANEL_PADDING_X {10};
constexpr int PANEL_PADDING_Y {10};
constexpr int PORT_SPACING_ROW {10};
constexpr int PORT_SPACING_COL {10};

class SwitchingPanel {
public:
	SwitchingPanel(int rows, int cols, Position origin);
	void move(int x, int y);
	int getVisualWidth() const;
	int getVisualHeight() const;
	static int getVisualWidth(int cols);
	static int getVisualHeight(int rows);

	int getPortClicked(int x, int y) const; // -1 if none
	Extension* getExtension(int number);
	const Extension* getExtension(int number) const;

	friend void View<SwitchingPanel>::draw();

private:
	int rows;
	int cols;
	Position origin;
	std::vector<Extension> extensions;
};

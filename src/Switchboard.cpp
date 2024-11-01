#include "Switchboard.h"
#include "raylib.h"

constexpr int SWITCHBOARD_PADDING {10};
constexpr int SWITCHBOARD_PANEL_MARGIN {10};
constexpr int SWITCHBOARD_DEFAULT_X {100};
constexpr int SWITCHBOARD_DEFAULT_Y {150};
constexpr int SWITCHBOARD_PANEL_X_LIMIT {700};
constexpr int SWITCHBOARD_PANEL_Y_LIMIT {500};

bool Switchboard::addPanel(int rows, int cols, int position) {
	int totalXSize = getVisualWidth() - (SWITCHBOARD_PADDING * 2);
	int largestY = getVisualHeight() - (SWITCHBOARD_PADDING * 2);

	// Account for newly added panel
	int newX = SwitchingPanel::getVisualWidth(cols);
	totalXSize += newX;

	// Check for vertical expansion
	int newY = SwitchingPanel::getVisualHeight(rows);
	if (largestY < newY) {
		largestY = newY;
	}

	// Check for size bounds breaking
	if (totalXSize > SWITCHBOARD_PANEL_X_LIMIT || largestY > SWITCHBOARD_PANEL_Y_LIMIT) {
		return false;
	}

	SwitchingPanel newPanel(rows, cols, {0,0});

	// Move the switchboard origin
	origin.x -= (newPanel.getVisualWidth() + SWITCHBOARD_PANEL_MARGIN) / 2;
	origin.y -= newPanel.getVisualHeight() / 2;

	// Add the new panel
	panels.push_back(newPanel);
	recenter();

	return true;
}

void Switchboard::move(int x, int y) {
	origin.x = x;
	origin.y = y;
	recenter();
}

int Switchboard::getVisualWidth() {
	int totalXSize{0};
	for (auto& panel : panels) {
		totalXSize += panel.getVisualWidth();
		totalXSize += SWITCHBOARD_PANEL_MARGIN;
	}

	if (panels.size() > 0) {
		totalXSize -= SWITCHBOARD_PANEL_MARGIN;
	}

	totalXSize += SWITCHBOARD_PADDING * 2;
	return totalXSize;
}

int Switchboard::getVisualHeight() {
	int largestY{0};
	for (auto& panel : panels) {
		int ySize = panel.getVisualHeight();
		if (largestY < ySize) {
			largestY = ySize;
		}
	}

	return largestY + (SWITCHBOARD_PADDING * 2);
}

Port Switchboard::getPortClicked(int x, int y) const {
	Port port;
	for (int i = 0; i < panels.size(); i++) {
		int portNum = panels[i].getPortClicked(x, y);
		if (portNum != -1) {
			port.portNum = portNum;
			port.boardNum = i;
		}
	}
	return port;
}

Extension* Switchboard::getExtension(Port port) {
	if (panels.size() > port.boardNum) {
		return panels[port.boardNum].getExtension(port.portNum);
	}
	return nullptr;
}

const Extension* Switchboard::getExtension(Port port) const {
	if (panels.size() > port.boardNum) {
		return panels[port.boardNum].getExtension(port.portNum);
	}
	return nullptr;
}

void Switchboard::recenter() {
	int currentX{origin.x + SWITCHBOARD_PADDING};
	for (auto& panel : panels) {
		int heightDiff = (getVisualHeight() - (SWITCHBOARD_PADDING * 2)) - panel.getVisualHeight();
		int currentY = origin.y + SWITCHBOARD_PADDING + (heightDiff / 2);
		panel.move(currentX, currentY);
		currentX += panel.getVisualWidth() + SWITCHBOARD_PANEL_MARGIN;
	}
}

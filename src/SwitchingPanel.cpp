#include "SwitchingPanel.h"

SwitchingPanel::SwitchingPanel(int rows, int cols, Position origin) : origin(origin), rows(rows), cols(cols) {
	int startX = origin.x + PANEL_PADDING_X + (EXTENSION_WIDTH/2);
	int startY = origin.y + PANEL_PADDING_Y + (EXTENSION_HEIGHT/2);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			int x = startX + (col * (EXTENSION_WIDTH + PORT_SPACING_COL));
			int y = startY + (row * (EXTENSION_HEIGHT + PORT_SPACING_ROW));
			extensions.push_back({(row * cols) + col, {x, y}});
		}
	}
}

void SwitchingPanel::move(int x, int y) {
	int deltaX = x - origin.x;
	int deltaY = y - origin.y;

	origin.x = x;
	origin.y = y;

	for (auto& ext : extensions) {
		ext.shift(deltaX, deltaY);
	}
}

int SwitchingPanel::getVisualWidth() const {
	return ((EXTENSION_WIDTH + PORT_SPACING_COL) * cols) - PORT_SPACING_COL + (PANEL_PADDING_X * 2);
}

int SwitchingPanel::getVisualHeight() const {
	return ((EXTENSION_HEIGHT + PORT_SPACING_ROW) * rows) - PORT_SPACING_ROW + (PANEL_PADDING_Y * 2);
}

int SwitchingPanel::getVisualWidth(int cols) {
	return ((EXTENSION_WIDTH + PORT_SPACING_COL) * cols) - PORT_SPACING_COL + (PANEL_PADDING_X * 2);
}

int SwitchingPanel::getVisualHeight(int rows) {
	return ((EXTENSION_HEIGHT + PORT_SPACING_ROW) * rows) - PORT_SPACING_ROW + (PANEL_PADDING_Y * 2);
}

int SwitchingPanel::getPortClicked(int x, int y) const {
	for (auto& ext : extensions) {
		if (ext.intersect(x, y)) {
			return ext.getNumber();
		}
	}

	return -1;
}

Extension* SwitchingPanel::getExtension(int number) {
	for (auto& ext : extensions) {
		if (ext.getNumber() == number) {
			return &ext;
		}
	}
	return nullptr;
}

const Extension* SwitchingPanel::getExtension(int number) const {
	for (auto& ext : extensions) {
		if (ext.getNumber() == number) {
			return &ext;
		}
	}
	return nullptr;
}

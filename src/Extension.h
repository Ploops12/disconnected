#pragma once

#include <algorithm>

#include "PhonePort.h"
#include "NumberPlate.h"
#include "IndicatorLight.h"
#include "Position.h"
#include "View.h"

constexpr int EXTENSION_ELEMENT_OFFSET {20};

constexpr int EXTENSION_WIDTH { std::max({INDICATOR_LIGHT_RADIUS, PHONE_PORT_RADIUS, NUMBER_PLATE_WIDTH}) };
constexpr int EXTENSION_HEIGHT { NUMBER_PLATE_HEIGHT + INDICATOR_LIGHT_RADIUS + PHONE_PORT_RADIUS + ((EXTENSION_ELEMENT_OFFSET * 2) - ((NUMBER_PLATE_HEIGHT / 2) + (INDICATOR_LIGHT_RADIUS / 2) + (PHONE_PORT_RADIUS / 2)) - 2)};

class PhoneJack;

class Extension {
public:
	Extension(int number, Position portCenter);
	void shift(int x, int y);
	friend void View<Extension>::draw();

	bool intersect(int x, int y) const;
	int getNumber() const { return label.number; }
	bool getJack() const { return jack; }
	Position getPortCenter() const { return port.center; }

	void insert(PhoneJack* jack);
	void disconnect();
	void setLight(bool state = true);

private:
	PhonePort port{{0,0}};
	NumberPlate label{0, {0,0}};
	IndicatorLight light;
	int number{0};
	PhoneJack* jack{nullptr};
};

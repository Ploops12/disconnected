#pragma once

#include "CircuitSwitch.h"
#include "PhoneJack.h"
#include "IndicatorLight.h"

enum class ControlType {
	NONE = 0,
	LIGHT1,
	LIGHT2,
	JACK1,
	JACK2,
	SW1,
	SW2
};

class CordCircuit {
public:
	CordCircuit(int id = 0, Position origin = {0,0});
	int getVisualWidth() const;
	int getVisualHeight() const;
	void move(int x, int y);

	ControlType getControlClicked(int x, int y) const;
	void* getControl(ControlType type);
	const void* getControl(ControlType type) const;

	void draw();

private:
	int id{0};
	Position origin{0,0};
	PhoneJack jack1{this, {0,0}};
	PhoneJack jack2{this, {0,0}, 1}; // Make this one red
	IndicatorLight light1;
	IndicatorLight light2;
	CircuitSwitch switch1;
	CircuitSwitch switch2 {1}; // Make this one red
};

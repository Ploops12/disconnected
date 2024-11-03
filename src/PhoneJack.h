#pragma once

#include "Position.h"
#include "CordSegment.h"
#include "Port.h"

class CordCircuit;
class Extension;
class PhoneJack;
extern bool isRed(PhoneJack* jack);

constexpr int PHONE_JACK_SHEATH_LEN {32};
constexpr int PHONE_JACK_LEAD_LEN {18};
constexpr int PHONE_JACK_SHEATH_WIDTH {12};
constexpr int PHONE_JACK_LEAD_WIDTH {7};
constexpr int PHONE_JACK_RADIUS {8};

class PhoneJack {
public:
	PhoneJack(CordCircuit* circuit, Position origin, int color = 0);
	Position getStart() { return origin; }
	Position getEnd();
	void move(int x, int y);
	void shift(int x, int y);
	bool intersect(int x, int y) const;

	void disconnect();
	void connect(Extension* ext);
	void grab();
	const CordCircuit* getCircuit() const;

	static int getLength() { return PHONE_JACK_LEAD_LEN + PHONE_JACK_SHEATH_LEN; }
	void draw();
	friend bool isRed(PhoneJack* jack);

private:
	Position origin{0,0};
	Position tetherPos{0,0};
	// 0: BLUE | 1: RED
	int color{0};
	float angle{0.0};
	bool grabbed{false};
	// TODO: Make this a vector of segments and implement IK
	CordSegment cord;
	Extension* extension{nullptr};
	CordCircuit* circuit{nullptr};
};

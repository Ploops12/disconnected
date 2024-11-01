#pragma once

#include "Position.h"
#include "CordSegment.h"
#include "View.h"
#include "Port.h"

constexpr int PHONE_JACK_SHEATH_LEN {32};
constexpr int PHONE_JACK_LEAD_LEN {18};
constexpr int PHONE_JACK_SHEATH_WIDTH {12};
constexpr int PHONE_JACK_LEAD_WIDTH {7};
constexpr int PHONE_JACK_RADIUS {8};

class PhoneJack {
public:
	PhoneJack(Position origin, int color = 0);
	Position getStart() { return origin; }
	Position getEnd();
	void move(int x, int y);
	void shift(int x, int y);

	bool intersect(int x, int y) const;
	void setGrab(bool grab);
	void setPort(Port port);
	Port getPort() const;
	void disconnect();

	static int getLength() { return PHONE_JACK_LEAD_LEN + PHONE_JACK_SHEATH_LEN; }
	friend void View<PhoneJack>::draw();

private:
	Position origin{0,0};
	Position tetherPos{0,0};
	// 0: BLUE | 1: RED
	int color{0};
	float angle{0.0};
	bool grabbed{false};
	Port connectedPort;
	// TODO: Make this a vector of segments and implement IK
	CordSegment cord;
};

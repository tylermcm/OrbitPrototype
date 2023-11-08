#pragma once
#include "position.h"

class Simulator;

class Element
{
public:
	Element(const Position& pos) : position(pos) {}

	virtual ~Element() {}
	virtual void updatePosition(Simulator& sim) = 0;

	Position getPosition() const { return position; }
	void setPosition(const Position& newPosition) { position = newPosition; }

protected:
	Position position;
};


#pragma once
#include "position.h"
#include "physics.h"

class Simulator;

class Element
{
public:
	Element(const Position& pos) : position(pos) {}

	virtual ~Element() {}
	virtual void updatePosition(Simulator& sim) = 0;

	Position getPosition() const { return position; }
	void setPosition(const Position& newPosition) { position = newPosition; }
	Physics& getPhysics() { return physics; }

protected:
	Position position;
	Physics physics;
};


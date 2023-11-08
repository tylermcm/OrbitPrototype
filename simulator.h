#pragma once
#include "physics.h"
#include "position.h"
#include "element.h"

class Simulator
{
public:
	void simulation(Element& element);
private:
	Physics physics;
	Position pos;
};


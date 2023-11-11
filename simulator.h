#pragma once
#include "physics.h"
#include "position.h"
#include "element.h"
class testSimulator;


class Simulator
{
public:
	friend testSimulator;
	void simulation(Element& element);
private:
	Physics physics;
	Position pos;
};


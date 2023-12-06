#pragma once
#include "satellite.h"

class Earth : public Satellite
{
public:
	Earth() : Satellite() {}

	void kill() override
	{

	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawEarth(position, angle);
	}

	void updatePosition(Simulator& sim) override
	{

	}
};


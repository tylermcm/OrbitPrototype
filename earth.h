#pragma once
#include "satellite.h"

class Earth : public Satellite
{
public:
	Earth() : Satellite()
	{
		this->radius = (6378000.00 / Position().getZoom()); // takes the diameter of earth and converts it to pixels
	}

	void kill() override
	{
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawEarth(position, angle);
	}

	void updatePosition(Simulator& sim) override
	{
		double rotationSpeed = -(2 * M_PI / 30.0) * 1440 / 86400;
		//calculates rotation speed of earth using pi, time dilation, and seconds in daay
		this->angle += rotationSpeed;
	}
};

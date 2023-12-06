#pragma once
#include "satellite.h"

class Fragment : public Satellite
{
public:
	Fragment(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 2;
	}
	Fragment() : Satellite() {}

	static Fragment* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		Fragment* newFragment = new Fragment(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newFragment->setInitialVelocity(velX, velY);
		return newFragment;
	}

	void kill() override {}
	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawFragment(this->getPosition(), angle);
	}
};


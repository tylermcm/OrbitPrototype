#pragma once
#include <vector>

#include "element.h"
#include "simulator.h"
#include "uiDraw.h"


class Satellite : public Element
{
public:
	Satellite(const Position& pos, double velX, double velY, double angle) : Element(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 10;
		this->numFragments = 2;
	}
	static Satellite* create(const Position& ptUpperRight);

	void updatePosition(Simulator& sim) override
	{
		sim.simulation(*this);
	}

	virtual void kill() = 0;

	virtual void draw(ogstream& gout, double angle) = 0;

};


class GPS : public Satellite
{
public:
	GPS(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 12;
		this->numFragments = 2;
	}

	static GPS* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		GPS* newGPS = new GPS(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newGPS->setInitialVelocity(velX, velY);
		return newGPS;
	}

	void kill() override
	{
		this->dead = true;
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawGPS(this->getPosition(), angle);
	}
};



class Sputnik : public Satellite
{
public:
	Sputnik(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 4;
		this->numFragments = 4;
	}
	static Sputnik* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		Sputnik* newSputnik = new Sputnik(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newSputnik->setInitialVelocity(velX, velY);
		return newSputnik;
	}

	void kill() override
	{
		this->dead = true;
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawSputnik(this->getPosition(), angle);
	}
};

class Hubble : public Satellite
{
public:
	Hubble(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 10;
		this->numFragments = 0;
	}
	static Hubble* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		Hubble* newHubble = new Hubble(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newHubble->setInitialVelocity(velX, velY);
		return newHubble;
	}

	void kill() override
	{
		this->dead = true;
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawHubble(this->getPosition(), angle);
	}

};

class Starlink : public Satellite
{
public:
	Starlink(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 6;
		this->numFragments = 2;
	}
	static Starlink* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		Starlink* newStarlink = new Starlink(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newStarlink->setInitialVelocity(velX, velY);
		return newStarlink;
	}

	void kill() override
	{
		this->dead = true;
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawStarlink(this->getPosition(), angle);
	}

};

class Dragon : public Satellite
{
public:
	Dragon(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle) 
	{
		this->dead = false;
		this->radius = 7;
		this->numFragments = 2;
	}
	static Dragon* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY, double angle)
	{
		Dragon* newDragon = new Dragon(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newDragon->setInitialVelocity(velX, velY);
		return newDragon;
	}

	void kill() override
	{
		this->dead = true;

	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawCrewDragon(this->getPosition(), angle);
	}

};
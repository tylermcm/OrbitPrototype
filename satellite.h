#pragma once
#include <vector>

#include "element.h"
#include "simulator.h"
#include "uiDraw.h"


class Satellite : public Element
{
public:
	Satellite(const Position& position) : Element(position) {}
	static Satellite* create(const Position& ptUpperRight);

	void updatePosition(Simulator& sim) override
	{
		sim.simulation(*this);
	}

	virtual void draw(ogstream& gout, double angle) = 0;

};


class GPS : public Satellite
{
public:
	GPS(const Position& position) : Satellite(position) {}

	static GPS* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY)
	{
		GPS* newGPS = new GPS(randomizePosition(ptUpperRight, posX, posY));
		newGPS->setInitialVelocity(velX, velY);
		return newGPS;
	}


	void draw(ogstream& gout, double angle) override
	{
		gout.drawGPS(this->getPosition(), angle);
	}
};



class Sputnik : public Satellite
{
public:
	Sputnik(const Position& position) : Satellite(position) {}
	static Sputnik* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY)
	{
		Sputnik* newSputnik = new Sputnik(randomizePosition(ptUpperRight, posX, posY));
		newSputnik->setInitialVelocity(velX, velY);
		return newSputnik;
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawSputnik(this->getPosition(), angle);
	}
};

class Hubble : public Satellite
{
public:
	Hubble(const Position& position) : Satellite(position) {}
	static Hubble* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY)
	{
		Hubble* newHubble = new Hubble(randomizePosition(ptUpperRight, posX, posY));
		newHubble->setInitialVelocity(velX, velY);
		return newHubble;
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawHubble(this->getPosition(), angle);
	}

};

class Starlink : public Satellite
{
public:
	Starlink(const Position& position) : Satellite(position) {}
	static Starlink* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY)
	{
		Starlink* newStarlink = new Starlink(randomizePosition(ptUpperRight, posX, posY));
		newStarlink->setInitialVelocity(velX, velY);
		return newStarlink;
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawStarlink(this->getPosition(), angle);
	}

};

class Dragon : public Satellite
{
public:
	Dragon(const Position& position) : Satellite(position) {}
	static Dragon* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY)
	{
		Dragon* newDragon = new Dragon(randomizePosition(ptUpperRight, posX, posY));
		newDragon->setInitialVelocity(velX, velY);
		return newDragon;
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawCrewDragon(this->getPosition(), angle);
	}

};
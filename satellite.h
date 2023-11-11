#pragma once
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

	static Position randomizePosition(const Position& ptUpperRight, double x, double y)
	{
		Position initialPos;
		initialPos.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
		initialPos.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
		initialPos.setMeters(x, y);
		return initialPos;
	}
};


class GPS : public Satellite
{
public:
	GPS(const Position& position) : Satellite(position) {}

	static GPS* create(const Position& position) {
		return new GPS(position);
	}

	static GPS* createRandomized(const Position& ptUpperRight)
	{
		return new GPS(randomizePosition(ptUpperRight, 0.0, 42164000));
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
	static Sputnik* create(const Position& ptUpperRight)
	{
		return new Sputnik(randomizePosition(ptUpperRight, 36515095.13, 21082000.0));
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
	static Hubble* create(const Position& ptUpperRight)
	{
		return new Hubble(randomizePosition(ptUpperRight, 0.0, 42164000));
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
	static Starlink* create(const Position& ptUpperRight)
	{
		return new Starlink(randomizePosition(ptUpperRight, 0.0, 13020000));
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
	static Dragon* create(const Position& ptUpperRight)
	{
		return new Dragon(randomizePosition(ptUpperRight, 0.0, 8000000));
	}

	void draw(ogstream& gout, double angle) override
	{
		gout.drawCrewDragon(this->getPosition(), angle);
	}

};
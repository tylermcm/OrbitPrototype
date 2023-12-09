/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#pragma once

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include <algorithm>  // used for min() and max()
#include "position.h" // Where things are drawn
using std::string;
using std::min;
using std::max;

#include <sstream>


#define GL_SILENCE_DEPRECATION

/*************************************************************************
 * GRAPHICS STREAM
 * A graphics stream that behaves much like COUT except on a drawn screen
 *************************************************************************/
class ogstream : public std::ostringstream
{
public:
	ogstream()
	{
	}

	ogstream(const Position& pt) : pt(pt)
	{
	}

	~ogstream() override { flush(); };

	// This is mostly for the text drawing stuff
	virtual void flush();

	virtual void setPosition(const Position& pt)
	{
		flush();
		this->pt = pt;
	}

	virtual ogstream& operator =(const Position& pt)
	{
		setPosition(pt);
		return *this;
	}

	// This is specific to the orbit simulator
	virtual void drawFragment(const Position& center, double rotation);
	virtual void drawProjectile(const Position& pt);

	virtual void drawCrewDragon(const Position& center, double rotation);
	virtual void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawCrewDragonCenter(const Position& center, double rotation);

	virtual void drawSputnik(const Position& center, double rotation);

	virtual void drawGPS(const Position& center, double rotation);
	virtual void drawGPSCenter(const Position& center, double rotation);
	virtual void drawGPSRight(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position());

	virtual void drawHubble(const Position& center, double rotation);
	virtual void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position());

	virtual void drawStarlink(const Position& center, double rotation);
	virtual void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position());
	virtual void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position());

	virtual void drawShip(const Position& center, double rotation, bool thrust);

	virtual void drawEarth(const Position& center, double rotation);

	virtual void drawStar(const Position& point, unsigned char phase);

protected:
	Position pt;
};

/*************************************************************************
 * GRAPHICS STREAM DUMMY
 * Better not be called!
 *************************************************************************/
class ogstreamDummy : public ogstream
{
public:
	ogstreamDummy(const Position& pt)
	{
	}

	~ogstreamDummy() override
	{
	}

	// This is mostly for the text drawing stuff
	void flush() override;
	void setPosition(const Position& pt) override;
	ogstreamDummy& operator =(const Position& pt) override;

	// This is specific to the orbit simulator
	void drawFragment(const Position& center, double rotation) override;
	void drawProjectile(const Position& pt) override;

	void drawCrewDragon(const Position& center, double rotation) override;
	void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawCrewDragonCenter(const Position& center, double rotation) override;

	void drawSputnik(const Position& center, double rotation) override;

	void drawGPS(const Position& center, double rotation) override;
	void drawGPSCenter(const Position& center, double rotation) override;
	void drawGPSRight(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawHubble(const Position& center, double rotation) override;
	void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawStarlink(const Position& center, double rotation) override;
	void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawShip(const Position& center, double rotation, bool thrust) override;

	void drawEarth(const Position& center, double rotation) override;

	void drawStar(const Position& point, unsigned char phase) override;
};

/*************************************************************************
 * GRAPHICS STREAM Fake
 * Better not be called!
 *************************************************************************/
class ogstreamFake : public ogstream
{
public:
	ogstreamFake(const Position& pt)
	{
	}

	~ogstreamFake() override
	{
	}

	// This is mostly for the text drawing stuff
	void flush() override;
	void setPosition(const Position& pt) override;
	ogstreamFake& operator =(const Position& pt) override;

	// This is specific to the orbit simulator
	void drawFragment(const Position& center, double rotation) override;
	void drawProjectile(const Position& pt) override;

	void drawCrewDragon(const Position& center, double rotation) override;
	void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawCrewDragonCenter(const Position& center, double rotation) override;

	void drawSputnik(const Position& center, double rotation) override;

	void drawGPS(const Position& center, double rotation) override;
	void drawGPSCenter(const Position& center, double rotation) override;
	void drawGPSRight(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawHubble(const Position& center, double rotation) override;
	void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawStarlink(const Position& center, double rotation) override;
	void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position()) override;
	void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position()) override;

	void drawShip(const Position& center, double rotation, bool thrust) override;

	void drawEarth(const Position& center, double rotation) override;

	void drawStar(const Position& point, unsigned char phase) override;
};

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer/double
 ****************************************************************/
int random(int min, int max);
double random(double min, double max);

// Declare rotate so it can be used by player class
Position rotate(const Position& origin, double x, double y, double rotation);

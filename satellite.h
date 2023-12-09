#pragma once
#include <vector>
#include "element.h"
#include "simulator.h"
#include "uiDraw.h"

enum class PartIdentifier
{
	// GPS parts
	GPSLeft,
	GPSCenter,
	GPSRight,
	// Hubble parts
	HubbleComputer,
	HubbleTelescope,
	HubbleLeft,
	HubbleRight,
	// Starlink parts
	StarlinkArray,
	StarlinkBody,
	// Dragon parts
	CrewDragonCenter,
	CrewDragonLeft,
	CrewDragonRight
};

struct gpsInitialVals
{
	Position pos;
	double velX;
	double velY;
};

/*************************************************************************
 * Satellite Class
 * Parent class to all the Satellites
 *************************************************************************/
class Satellite : public Element
{
protected:
	static std::vector<Satellite*>* satellitesList;

public:
	Satellite(const Position& pos, double velX, double velY, double angle) : Element(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 10;
		this->numFragments = 2;
	}

	Satellite() : Element()
	{
	}

	static Satellite* create(const Position& ptUpperRight);
	static const std::vector<gpsInitialVals>& getGpsData();
	static void setSatellitesList(std::vector<Satellite*>* list) { satellitesList = list; }

	void updatePosition(Simulator& sim) override
	{
		sim.simulation(*this);
	}

	void kill() override = 0;

	virtual void update(double elapsedTime, double realTimeElapsed)
	{
	};

	virtual void createParts(Position pos, double newVelX, double newVelY)
	{
	};

	virtual void draw(ogstream& gout, double angle) = 0;

	bool isDead() const { return dead; }
};


/*************************************************************************
 * Fragment Class
 * Class representing Fragments of satellites
 *************************************************************************/
class Fragment : public Satellite
{
public:
	Fragment(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)

	{
		this->dead = false;
		this->radius = 2;
		this->angle = angle;
	}

	static Fragment* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY,
	                        double angle)
	{
		auto newFragment = new Fragment(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newFragment->setInitialVelocity(velX, velY);
		return newFragment;
	}

	void update(double angle)
	{
		constexpr double spinRate = 0.5;
		this->angle = angle + spinRate;
	}

	void kill() override
	{
		this->dead = true;
	}

	//Probably shouldn't call update in draw, but its the only place passing in angle at the moment.
	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
		{
			gout.drawFragment(this->getPosition(), this->angle);
			update(angle);
		}
	}
};


/*************************************************************************
 * Part Class
 * Class representing Parts of satellites
 *************************************************************************/
class Part : public Satellite
{
public:
	Part(const Position& pos, double velX, double velY, double angle, PartIdentifier identifier)
		: Satellite(pos, velX, velY, angle), partIdentifier(identifier)
	{
		this->dead = false;
		this->radius = 2;
		this->angle = angle;
	}

	static Part* create(const Position& ptUpperRight, double posX, double posY,
	                    double velX, double velY, double angle,
	                    PartIdentifier identifier)
	{
		auto newPart = new Part(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle, identifier);
		newPart->setInitialVelocity(velX, velY);
		return newPart;
	}

	void update(double angle)
	{
	}

	void kill() override
	{
		this->dead = true;
	}

	void Part::draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
		{
			switch (partIdentifier)
			{
			case PartIdentifier::GPSLeft:
				gout.drawGPSLeft(this->getPosition(), angle);
				break;
			case PartIdentifier::GPSCenter:
				gout.drawGPSCenter(this->getPosition(), angle);
				break;
			case PartIdentifier::GPSRight:
				gout.drawGPSRight(this->getPosition(), angle);
				break;
			case PartIdentifier::HubbleComputer:
				gout.drawHubbleComputer(this->getPosition(), angle);
				break;
			case PartIdentifier::HubbleTelescope:
				gout.drawHubbleTelescope(this->getPosition(), angle);
				break;
			case PartIdentifier::HubbleLeft:
				gout.drawHubbleLeft(this->getPosition(), angle);
				break;
			case PartIdentifier::HubbleRight:
				gout.drawHubbleRight(this->getPosition(), angle);
				break;
			case PartIdentifier::StarlinkArray:
				gout.drawStarlinkArray(this->getPosition(), angle);
				break;
			case PartIdentifier::StarlinkBody:
				gout.drawStarlinkBody(this->getPosition(), angle);
				break;
			case PartIdentifier::CrewDragonCenter:
				gout.drawCrewDragonCenter(this->getPosition(), angle);
				break;
			case PartIdentifier::CrewDragonLeft:
				gout.drawCrewDragonLeft(this->getPosition(), angle);
				break;
			case PartIdentifier::CrewDragonRight:
				gout.drawCrewDragonRight(this->getPosition(), angle);
				break;
			}
		}
	}

private:
	PartIdentifier partIdentifier;
};


/*************************************************************************
 * GPS Class
 * Class representing GPS satellite
 *************************************************************************/
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
		auto newGPS = new GPS(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newGPS->setInitialVelocity(velX, velY);
		return newGPS;
	}

	void kill() override
	{
		this->dead = true;
		const double spreadAngle = 360.0 / numFragments;
		constexpr double distance = 4;

		Position fragmentPosition;
		double newVelX;
		double newVelY;

		for (int i = 0; i < numFragments; i++)
		{
			double angleRad = (this->getAngle() + i * spreadAngle) * M_PI / 180.0;

			double offsetX = distance * cos(angleRad);
			double offsetY = distance * sin(angleRad);

			fragmentPosition = this->getPosition();
			fragmentPosition.addPixelsX(offsetX);
			fragmentPosition.addPixelsY(offsetY);

			int randomSpeed = random(5000.0, 9000.0);
			newVelX = this->getPhysics().getVelocityX() + randomSpeed;
			newVelY = this->getPhysics().getVelocityY() + randomSpeed;

			Fragment* fragment = Fragment::create(fragmentPosition, fragmentPosition.getMetersX(),
			                                      fragmentPosition.getMetersY(), newVelX,
			                                      this->getPhysics().getVelocityY(),
			                                      this->getAngle());
			satellitesList->push_back(fragment);
		}

		createParts(fragmentPosition, newVelX, newVelY);
	}

	void createParts(Position pos, double newVelX, double newVelY) override
	{
		constexpr double partOffsetDistance = 20.0;

		Position centerPosition = pos;
		Part* centerPart = Part::create(centerPosition, centerPosition.getMetersX(), centerPosition.getMetersY(),
		                                this->getPhysics().getVelocityX(), newVelY, this->getAngle(),
		                                PartIdentifier::GPSCenter);

		Position leftPosition = pos;
		leftPosition.addPixelsX(-partOffsetDistance);
		Part* leftPart = Part::create(leftPosition, leftPosition.getMetersX(), leftPosition.getMetersY(), -newVelX,
		                              this->getPhysics().getVelocityY(), this->getAngle(), PartIdentifier::GPSLeft);

		Position rightPosition = pos;
		rightPosition.addPixelsX(partOffsetDistance);
		Part* rightPart = Part::create(rightPosition, rightPosition.getMetersX(), rightPosition.getMetersY(), newVelX,
		                               this->getPhysics().getVelocityY(), this->getAngle(), PartIdentifier::GPSRight);

		satellitesList->push_back(centerPart);
		satellitesList->push_back(leftPart);
		satellitesList->push_back(rightPart);
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawGPS(this->getPosition(), angle);
	}

	void updatePosition(Simulator& sim) override
	{
		this->angle = physics.
			directionOfGravityPull(this->getPosition().getMetersX(), this->getPosition().getMetersY());
		this->angle += 90 * (3.14159265358979323846 / 180);
		sim.simulation(*this);
	}
};


/*************************************************************************
 * Sputnik Class
 * Class representing Sputnik satellite
 *************************************************************************/

class Sputnik : public Satellite
{
public:
	Sputnik(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 4;
		this->numFragments = 4;
	}

	static Sputnik* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY,
	                       double angle)
	{
		auto newSputnik = new Sputnik(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newSputnik->setInitialVelocity(velX, velY);
		return newSputnik;
	}

	void kill() override
	{
		this->dead = true;
		const double spreadAngle = 360.0 / numFragments;
		constexpr double distance = 4;

		Position fragmentPosition;
		double newVelX;
		double newVelY;

		for (int i = 0; i < numFragments; i++)
		{
			double angleRad = (this->getAngle() + i * spreadAngle) * M_PI / 180.0;

			double offsetX = distance * cos(angleRad);
			double offsetY = distance * sin(angleRad);

			fragmentPosition = this->getPosition();
			fragmentPosition.addPixelsX(offsetX);
			fragmentPosition.addPixelsY(offsetY);

			int randomSpeed = random(5000.0, 9000.0);
			newVelX = this->getPhysics().getVelocityX() + randomSpeed;
			newVelY = this->getPhysics().getVelocityY() + randomSpeed;

			Fragment* fragment = Fragment::create(fragmentPosition, fragmentPosition.getMetersX(),
			                                      fragmentPosition.getMetersY(), newVelX,
			                                      this->getPhysics().getVelocityY(),
			                                      this->getAngle());
			satellitesList->push_back(fragment);
		}
	}


	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawSputnik(this->getPosition(), angle);
	}
};


/*************************************************************************
 * Hubble Class
 * Class representing Hubble satellite
 *************************************************************************/
class Hubble : public Satellite
{
public:
	Hubble(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 10;
		this->numFragments = 0;
	}

	static Hubble* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY,
	                      double angle)
	{
		auto newHubble = new Hubble(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newHubble->setInitialVelocity(velX, velY);
		return newHubble;
	}

	void kill() override
	{
		this->dead = true;

		int randomSpeed = random(5000.0, 9000.0);
		double newVelX = this->getPhysics().getVelocityX() + randomSpeed;
		double newVelY = this->getPhysics().getVelocityY() + randomSpeed;

		Position fragmentPosition = this->getPosition();
		createParts(fragmentPosition, newVelX, newVelY);
	}


	void createParts(Position pos, double newVelX, double newVelY) override
	{
		constexpr double partOffsetDistance = 20.0;

		Position computerPosition = pos;
		Part* computerPart = Part::create(computerPosition, computerPosition.getMetersX(),
		                                  computerPosition.getMetersY(), this->getPhysics().getVelocityX(), newVelY,
		                                  this->getAngle(), PartIdentifier::HubbleComputer);

		Position telescopePosition = pos;
		Part* telescopePart = Part::create(telescopePosition, telescopePosition.getMetersX(),
		                                   telescopePosition.getMetersY(), this->getPhysics().getVelocityX(), -newVelY,
		                                   this->getAngle(), PartIdentifier::HubbleTelescope);

		Position leftPosition = pos;
		leftPosition.addPixelsX(-partOffsetDistance);
		Part* leftPart = Part::create(leftPosition, leftPosition.getMetersX(), leftPosition.getMetersY(), -newVelX,
		                              this->getPhysics().getVelocityY(), this->getAngle(), PartIdentifier::HubbleLeft);

		Position rightPosition = pos;
		rightPosition.addPixelsX(partOffsetDistance);
		Part* rightPart = Part::create(rightPosition, rightPosition.getMetersX(), rightPosition.getMetersY(), newVelX,
		                               this->getPhysics().getVelocityY(), this->getAngle(),
		                               PartIdentifier::HubbleRight);

		satellitesList->push_back(computerPart);
		satellitesList->push_back(telescopePart);
		satellitesList->push_back(leftPart);
		satellitesList->push_back(rightPart);
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawHubble(this->getPosition(), angle);
	}
};


/*************************************************************************
 * Starlink Class
 * Class representing Starlink satellite
 *************************************************************************/
class Starlink : public Satellite
{
public:
	Starlink(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 6;
		this->numFragments = 2;
	}

	static Starlink* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY,
	                        double angle)
	{
		auto newStarlink = new Starlink(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newStarlink->setInitialVelocity(velX, velY);
		return newStarlink;
	}

	void kill() override
	{
		this->dead = true;
		const double spreadAngle = 360.0 / numFragments;
		constexpr double distance = 4;

		Position fragmentPosition;
		double newVelX;
		double newVelY;

		for (int i = 0; i < numFragments; i++)
		{
			double angleRad = (this->getAngle() + i * spreadAngle) * M_PI / 180.0;

			double offsetX = distance * cos(angleRad);
			double offsetY = distance * sin(angleRad);

			fragmentPosition = this->getPosition();
			fragmentPosition.addPixelsX(offsetX);
			fragmentPosition.addPixelsY(offsetY);

			int randomSpeed = random(5000.0, 9000.0);
			newVelX = this->getPhysics().getVelocityX() + randomSpeed;
			newVelY = this->getPhysics().getVelocityY() + randomSpeed;

			Fragment* fragment = Fragment::create(fragmentPosition, fragmentPosition.getMetersX(),
			                                      fragmentPosition.getMetersY(), newVelX,
			                                      this->getPhysics().getVelocityY(),
			                                      this->getAngle());
			satellitesList->push_back(fragment);
		}

		createParts(fragmentPosition, newVelX, newVelY);
	}

	void createParts(Position pos, double newVelX, double newVelY) override
	{
		constexpr double partOffsetDistance = 20.0;

		Position bodyPosition = pos;
		Part* bodyPart = Part::create(bodyPosition, bodyPosition.getMetersX(), bodyPosition.getMetersY(), newVelX,
		                              this->getPhysics().getVelocityY(), this->getAngle(),
		                              PartIdentifier::StarlinkBody);

		Position arrayPosition = pos;
		arrayPosition.addPixelsX(-partOffsetDistance);
		Part* arrayPart = Part::create(arrayPosition, arrayPosition.getMetersX(), arrayPosition.getMetersY(), -newVelX,
		                               this->getPhysics().getVelocityY(), this->getAngle(),
		                               PartIdentifier::StarlinkArray);


		satellitesList->push_back(bodyPart);
		satellitesList->push_back(arrayPart);
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawStarlink(this->getPosition(), angle);
	}
};


/*************************************************************************
 * Dragon Class
 * Class representing Dragon satellite
 *************************************************************************/
class Dragon : public Satellite
{
public:
	Dragon(const Position& pos, double velX, double velY, double angle) : Satellite(pos, velX, velY, angle)
	{
		this->dead = false;
		this->radius = 7;
		this->numFragments = 2;
	}

	static Dragon* create(const Position& ptUpperRight, double posX, double posY, double velX, double velY,
	                      double angle)
	{
		auto newDragon = new Dragon(randomizePosition(ptUpperRight, posX, posY), velX, velY, angle);
		newDragon->setInitialVelocity(velX, velY);
		return newDragon;
	}

	void kill() override
	{
		this->dead = true;
		const double spreadAngle = 360.0 / numFragments;
		constexpr double distance = 4;

		Position fragmentPosition;
		double newVelX;
		double newVelY;

		for (int i = 0; i < numFragments; i++)
		{
			double angleRad = (this->getAngle() + i * spreadAngle) * M_PI / 180.0;

			double offsetX = distance * cos(angleRad);
			double offsetY = distance * sin(angleRad);

			fragmentPosition = this->getPosition();
			fragmentPosition.addPixelsX(offsetX);
			fragmentPosition.addPixelsY(offsetY);

			int randomSpeed = random(5000.0, 9000.0);
			newVelX = this->getPhysics().getVelocityX() + randomSpeed;
			newVelY = this->getPhysics().getVelocityY() + randomSpeed;

			Fragment* fragment = Fragment::create(fragmentPosition, fragmentPosition.getMetersX(),
			                                      fragmentPosition.getMetersY(), newVelX,
			                                      this->getPhysics().getVelocityY(),
			                                      this->getAngle());
			satellitesList->push_back(fragment);
		}

		createParts(fragmentPosition, newVelX, newVelY);
	}

	void createParts(Position pos, double newVelX, double newVelY) override
	{
		constexpr double partOffsetDistance = 20.0;

		Position centerPosition = pos;
		Part* centerPart = Part::create(centerPosition, centerPosition.getMetersX(), centerPosition.getMetersY(),
		                                this->getPhysics().getVelocityX(), newVelY, this->getAngle(),
		                                PartIdentifier::CrewDragonCenter);

		Position leftPosition = pos;
		leftPosition.addPixelsX(-partOffsetDistance);
		Part* leftPart = Part::create(leftPosition, leftPosition.getMetersX(), leftPosition.getMetersY(), -newVelX,
		                              this->getPhysics().getVelocityY(), this->getAngle(),
		                              PartIdentifier::CrewDragonLeft);

		Position rightPosition = pos;
		rightPosition.addPixelsX(partOffsetDistance);
		Part* rightPart = Part::create(rightPosition, rightPosition.getMetersX(), rightPosition.getMetersY(), newVelX,
		                               this->getPhysics().getVelocityY(), this->getAngle(),
		                               PartIdentifier::CrewDragonRight);

		satellitesList->push_back(centerPart);
		satellitesList->push_back(leftPart);
		satellitesList->push_back(rightPart);
	}

	void draw(ogstream& gout, double angle) override
	{
		if (!this->dead)
			gout.drawCrewDragon(this->getPosition(), angle);
	}
};

#pragma once
#include "position.h"
#include "physics.h"
#include "uiDraw.h"

class Simulator;

class Element
{
public:
    Element(const Position& pos, double velX, double velY, double angle)
    {
        this->position = pos;
        this->velX = velX;
        this->velY = velY;
        this->angle = angle;
    }

    virtual ~Element() {}
    virtual void updatePosition(Simulator& sim) = 0;

    Position getPosition() const { return position; }
    void setPosition(const Position& newPosition) { position = newPosition; }
    double getAngle() const { return angle; }
    Physics& getPhysics() { return physics; }

    void setInitialVelocity(double velX, double velY)
    {
        physics.setVelocityX(velX);
        physics.setVelocityY(velY);
    }

    static Position randomizePosition(const Position& ptUpperRight, double x, double y)
    {
        Position initialPos;
        initialPos.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        initialPos.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        initialPos.setMeters(x, y);
        return initialPos;
    }

protected:
    Position position;
    Physics physics;
    double velX;
    double velY;
    double angle;
};

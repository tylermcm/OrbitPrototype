#pragma once
#include "position.h"
#include "uiDraw.h"
#include "physics.h"
#include "satellite.h"

class Projectile : public Satellite {
public:
    Projectile() : active(false), lifetime(0.0), velocity(0.0) {}
    Projectile(const Position& startPosition, double angle_, double additionalVelocity) {
        this->position = startPosition;
        this->angle = angle_;
        this->velocity = additionalVelocity;
        this->dead = false;
        this->lifetime = 0.0;
        this->realTimeLifetime = 0.0;
        this->radius = 2.0;
    }


    Position getPosition() const {
        return position;
    }


    void update(double elapsedTime, double realTimeElapsed) {
        if (!active) return;

        realTimeLifetime += realTimeElapsed;
        if (realTimeLifetime > 2.0) {
            kill();
            return;
        }

        double dx = physics.computeHorizontalComponent(velocity, angle) * elapsedTime;
        double dy = physics.computeVerticalComponent(velocity, angle) * elapsedTime;

        position.addMetersX(dx);
        position.addMetersY(dy);
    }


    void draw(ogstream& gout, double angle) override
	{
        if (active) {
            gout.drawProjectile(position);
        }
    }
    void kill() override
    {
        dead = true;
    }

    bool isActive() const { return active; }

private:
    double velocity;
    bool active;
    double lifetime;
    double realTimeLifetime;
};

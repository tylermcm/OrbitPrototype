#pragma once
#include "position.h"
#include "uiDraw.h"
#include "physics.h"

class Projectile {
public:
    Projectile() : active(false), lifetime(0.0), velocity(0.0) {}
    Projectile(const Position& startPosition, double angle, double additionalVelocity)
        : position(startPosition), angle(angle), velocity(additionalVelocity),
        active(true), lifetime(0.0), realTimeLifetime(0.0) {}


    Position getPosition() const {
        return position;
    }

    void update(double elapsedTime, double realTimeElapsed) {
        if (!active) return;

        realTimeLifetime += realTimeElapsed;
        if (realTimeLifetime > 2.0) {
            active = false;
            return;
        }
        double dx = physics.computeHorizontalComponent(velocity, angle) * elapsedTime;
        double dy = physics.computeVerticalComponent(velocity, angle) * elapsedTime;

        position.addMetersX(dx);
        position.addMetersY(dy);
    }

    void draw(ogstream& gout) const {
        if (active) {
            gout.drawProjectile(position);
        }
    }

    bool isActive() const { return active; }

private:
    Position position;
    Physics physics;
    double angle;
    double velocity;
    bool active;
    double lifetime;
    double realTimeLifetime;

};
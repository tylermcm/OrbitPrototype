#pragma once
#include <cmath>
#include <corecrt_math_defines.h>


class Physics
{
public:
    double getVelocityX()     const { return velocityX; }
    double getVelocityY()     const { return velocityY; }
    double getTimePerFrame()  const { return timePerFrame; }
    double getRotationSpeed() const { return rotationSpeed; }

    void setVelocityX(double velX) { velocityX = velX; }
    void setVelocityY(double velY) { velocityY = velY; }

    double computeGravity(double h) const;
    double heightAboveEarth(double x, double y) const;
    double directionOfGravityPull(double xs, double ys) const;
    double computeHorizontalComponent(double a, double angle) const;
    double computeVerticalComponent(double a, double angle) const;
    double newPosition(double s0);
    double computeMotion(double s0, double v, double t);
    double computeHorizontalPosition(double x0, double dx, double t);
    double computeVerticalPosition(double y0, double dy, double t);
    double computeDistance(double s0, double v, double t, double a);
    double computeVelocity(double v0, double a, double t);


private:
    double velocityX = -3100.0;
    double velocityY = 0.0;
    double timeDilation = 24 * 60;
    double timePerFrame = timeDilation / 30;
    double rotationSpeed = -(2 * M_PI / 30) * (timeDilation / 86400);

};





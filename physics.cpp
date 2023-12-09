#include "physics.h"

// Function to compute the magnitude of acceleration due to gravity at an altitude (h)
double Physics::computeGravity(double h) const {
    const double g = 9.80665; // gravity at sea level in m/s^2
    const double r = 6378000; // radius of the Earth in meters

    double gh = g * pow((r / (r + h)), 2);
    return gh;
}

// Function to compute the height above the Earth in meters
double Physics::heightAboveEarth(double x, double y) const {
    const double r = 6378000; // radius of the Earth in meters

    double h = sqrt(pow(x, 2) + pow(y, 2)) - r;
    return h;
}

// Function to compute the direction of the pull of gravity in radians
double Physics::directionOfGravityPull(double xs, double ys) const {
    double xe = 0;
    double ye = 0;
    double d = atan2(xe - xs,ye - ys);
    return d;
}

// Function to compute the horizontal component of acceleration
double Physics::computeHorizontalComponent(double a, double angle) const {
    double ddx = a * sin(angle);
    return ddx;
}

// Function to compute the vertical component of acceleration
double Physics::computeVerticalComponent(double a, double angle) const {
    double ddy = a * cos(angle);
    return ddy;
}
// Newton's first law: st = s0
double Physics::newPosition(double s0) {
    return s0;
}

// Motion with constant velocity: s = s0 + v * t
double Physics::computeMotion(double s0, double v, double t) {
    return s0 + v * t;
}

// Horizontal position with constant velocity: xt = x0 + dx * t
double Physics::computeHorizontalPosition(double x0, double dx, double t) {
    return x0 + dx * t;
}

// Vertical position with constant velocity: yt = y0 + dy * t
double Physics::computeVerticalPosition(double y0, double dy, double t) {
    return y0 + dy * t;
}

// Distance formula with acceleration: s = s0 + v * t + 0.5 * a * t^2
double Physics::computeDistance(double s0, double v, double t, double a) {
    return s0 + v * t + 0.5 * a * std::pow(t, 2);
}

// Velocity with constant acceleration: v = v0 + a * t
double Physics::computeVelocity(double v0, double a, double t) {
    return v0 + a * t;
}


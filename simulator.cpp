#include "simulator.h"



void Simulator::simulation(Element& element)
{
    Position pos = element.getPosition();

    // Calculate gravitational acceleration at the element's current position.
    const double acceleration = physics.computeGravity(
        physics.heightAboveEarth(pos.getMetersX(), pos.getMetersY())
    );

    // Calculate the direction of the gravity pull.
    const double angle = physics.directionOfGravityPull(
        pos.getMetersX(), pos.getMetersY()
    );

    // Compute the components of acceleration.
    const double ddx = physics.computeHorizontalComponent(acceleration, angle);
    const double ddy = physics.computeVerticalComponent(acceleration, angle);

    // Update the element's velocity based on the acceleration and time per frame.
    const double newVelocityX = physics.getVelocityX() + ddx * physics.getTimePerFrame();
    const double newVelocityY = physics.getVelocityY() + ddy * physics.getTimePerFrame();

    // Set the new velocities in the Physics object.
    physics.setVelocityX(newVelocityX);
    physics.setVelocityY(newVelocityY);

    // Update the position based on the new velocity.
    const double newPosX = physics.computeDistance(
        pos.getMetersX(), physics.getVelocityX(), physics.getTimePerFrame(), ddx
    );
    const double newPosY = physics.computeDistance(
        pos.getMetersY(), physics.getVelocityY(), physics.getTimePerFrame(), ddy
    );

    // Set the new position for the element.
    element.setPosition(Position(newPosX, newPosY));
}

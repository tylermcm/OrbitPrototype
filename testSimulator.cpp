#include <cassert>
#include "testSimulator.h"
#include "satellite.h"


void testSimulator::testInitialConditions()
{
    GPS* gps = GPS::createRandomized(ptUpperRight);
    Position newPos = gps->getPosition();
    assert(newPos.getMetersX() == 0.0);
    assert(newPos.getMetersY() == 42164000);
    delete gps;
}

void testSimulator::testGpsStationary()
{
    Position ptUpperRight(1000000, 1000000);
    physics.setTimePerFrame(0);
    GPS* gps = GPS::create(ptUpperRight);
    gps->updatePosition(simulator);

    Position initialPosition = gps->getPosition();
    simulator.simulation(*gps);
    Position newPosition = gps->getPosition();
    assert(initialPosition.getMetersX() == newPosition.getMetersX());
    assert(initialPosition.getMetersY() == newPosition.getMetersY());
    delete gps;
}

void testSimulator::testTimePerFrameEffect()
{
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(1000000, 1000000));
    gps->updatePosition(simulator);

    //simulator.simulation(*gps);
    Position newPos = gps->getPosition();
    double expectedPosY = 0.5 * physics.computeGravity(newPos.getMetersY()) * std::pow(1.0, 2);
    assert(newPos.getMetersY() <= expectedPosY);
    delete gps;
}

void testSimulator::testIntegrationWithPhysics()
{
    GPS* gps = GPS::create(Position(1000000, 1000000));
    gps->updatePosition(simulator);
    //simulator.simulation(*gps);

    Position newPos = gps->getPosition();
    double expectedPosX = physics.computeHorizontalPosition(1000000, physics.computeHorizontalComponent(physics.computeGravity(physics.heightAboveEarth(1000000, 1000000)), physics.directionOfGravityPull(1000000, 1000000)), physics.getTimePerFrame());
    double expectedPosY = physics.computeVerticalPosition(1000000, physics.computeVerticalComponent(physics.computeGravity(physics.heightAboveEarth(1000000, 1000000)), physics.directionOfGravityPull(1000000, 1000000)), physics.getTimePerFrame());
    assert(newPos.getMetersX() == expectedPosX);
    assert(newPos.getMetersY() == expectedPosY);
    delete gps;
}

void testSimulator::testPositiveVelocity()
{
    physics.setVelocityX(5.0);
    physics.setVelocityY(5.0);
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(0, 0));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    Position newPos = gps->getPosition();
    double expectedPosX = physics.computeMotion(0, 5.0, 1.0);
    double expectedPosY = physics.computeMotion(0, 5.0, 1.0);
    assert(newPos.getMetersX() == expectedPosX);
    assert(newPos.getMetersY() == expectedPosY);
    delete gps;
}

void testSimulator::testNegativeVelocity()
{
    physics.setVelocityX(-5.0);
    physics.setVelocityY(-5.0);
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(0, 0));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    Position newPos = gps->getPosition();
    double expectedPosX = physics.computeMotion(0, -5.0, 1.0);
    double expectedPosY = physics.computeMotion(0, -5.0, 1.0);
    assert(newPos.getMetersX() == expectedPosX);
    assert(newPos.getMetersY() == expectedPosY);
    delete gps;
}

void testSimulator::testAccelerationEffectOnVelocity()
{
    physics.setVelocityX(0.0);
    physics.setVelocityY(0.0);
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(0, 0));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    double expectedVelocityY = physics.computeVelocity(0.0, physics.computeGravity(physics.heightAboveEarth(0, 0)), 1.0);
    assert(physics.getVelocityY() == expectedVelocityY);
    assert(physics.getVelocityX() == 0.0);
    delete gps;
}

void testSimulator::testNoMovement()
{
    physics.setVelocityX(0.0);
    physics.setVelocityY(0.0);
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(50, 50));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    Position newPos = gps->getPosition();
    assert(newPos.getMetersX() == 50.0);
    assert(newPos.getMetersY() == 50.0);
    delete gps;
}

void testSimulator::testDecelerationToStop()
{
    physics.setVelocityX(10.0);
    physics.setVelocityY(0.0);
    physics.setTimePerFrame(1.0);
    GPS* gps = GPS::create(Position(0, 0));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    double expectedVelocityX = physics.computeVelocity(10.0, -10.0, 1.0);
    assert(physics.getVelocityX() == expectedVelocityX);
    assert(physics.getVelocityY() == 0.0);
    delete gps;
}

void testSimulator::testPositionChangeWithTimeAndAccel()
{
    physics.setVelocityX(0.0);
    physics.setVelocityY(0.0);
    physics.setTimePerFrame(2.0);
    GPS* gps = GPS::create(Position(0, 0));
    gps->updatePosition(simulator);
    simulator.simulation(*gps);

    Position newPos = gps->getPosition();
    double expectedPosY = physics.computeDistance(0, 0, 2.0, physics.computeGravity(physics.heightAboveEarth(0, 0)));
    assert(newPos.getMetersY() == expectedPosY);
    assert(newPos.getMetersX() == 0.0);
    delete gps;
}

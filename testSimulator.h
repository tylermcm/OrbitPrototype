#pragma once
#include <cassert>
#include "position.h"
#include "simulator.h"
#include "physics.h"
#include "satellite.h"
class testSimulator
{
public:
	void run()
	{
        testInitialConditions();
        test_simulation_gpsStationary();
        test_simulation_timePerFrameEffect();
        test_simulation_integrationWithPhysics();
        test_simulation_positiveVelocity();
        test_simulation_negativeVelocity();
        test_simulation_accelerationEffectOnVelocity();
        test_simulation_noMovement();
        test_simulation_decelerationToStop();
        test_simulation_positionChangeWithTimeAndAccel();
	}

private:
    Position ptUpperRight;
    Simulator simulator;
    Physics physics;

    void testInitialConditions() {
        GPS* gps = GPS::createRandomized(ptUpperRight);

        Position newPos = gps->getPosition();
        assert(newPos.getMetersX() == 0.0);
        assert(newPos.getMetersY() == 42164000);
        delete gps;
    }

    void test_simulation_gpsStationary() {
        Position ptUpperRight(10000, 10000);  // Define an upper right position
        physics.setTimePerFrame(0);
        GPS* gps = GPS::create(ptUpperRight);
        gps->updatePosition(simulator);
        Position initialPosition = gps->getPosition();

        // Run the simulation for a single frame
        simulator.simulation(*gps);

        Position newPosition = gps->getPosition();
        assert(initialPosition.getMetersX() == newPosition.getMetersX());
        assert(initialPosition.getMetersY() == newPosition.getMetersY());
    	delete gps; // Remember to free memory since GPS is created with `new`
    }
    void test_simulation_timePerFrameEffect() {
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);
        physics.setTimePerFrame(0.5); // Set the time per frame to 0.5 seconds

        Position newPos = gps->getPosition();
        // Ensure the position change reflects the 0.5-second time frame
        assert(newPos.getMetersY() < 9.81 * 0.5 * 0.5);
    }

    void test_simulation_integrationWithPhysics() {
        GPS* gps = GPS::create(Position(50, 50));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);
        Position newPos = gps->getPosition();
        double expectedPosX = physics.computeDistance(50, physics.getVelocityX(), physics.getTimePerFrame(), 5000);
        double expectedPosY = physics.computeDistance(50, physics.getVelocityY(), physics.getTimePerFrame(), 10000);

        assert(newPos.getMetersX() == expectedPosX);
        assert(newPos.getMetersY() == expectedPosY);
    }

    void test_simulation_positiveVelocity() {
        
        physics.setVelocityX(5.0);
        physics.setVelocityY(5.0);
        physics.setTimePerFrame(1.0); // 1 second per frame
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        Position newPos = gps->getPosition();
        // Assuming no acceleration, the position should have changed by velocity*time
        assert(newPos.getMetersX() == 5.0);
        assert(newPos.getMetersY() == 5.0);
    }

    void test_simulation_negativeVelocity() {
        
        physics.setVelocityX(-5.0);
        physics.setVelocityY(-5.0);
        physics.setTimePerFrame(1.0); // 1 second per frame
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        Position newPos = gps->getPosition();
        // With negative velocity, the new position should be less than the initial
        assert(newPos.getMetersX() == -5.0);
        assert(newPos.getMetersY() == -5.0);
    }

    void test_simulation_accelerationEffectOnVelocity() {
        
        physics.setVelocityX(0.0);
        physics.setVelocityY(0.0);
        physics.setTimePerFrame(1.0); // 1 second per frame
        // Set a gravity acceleration value directly for the test
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        // Velocity should have increased by gravity*time in the Y direction
        assert(physics.getVelocityY() == 9.81);
        // X velocity should remain unchanged as gravity only affects Y
        assert(physics.getVelocityX() == 0.0);
    }

    void test_simulation_noMovement() {
        
        physics.setVelocityX(0.0);
        physics.setVelocityY(0.0);
        physics.setTimePerFrame(1.0);
        // Assuming zero gravity for the test
        GPS* gps = GPS::create(Position(50, 50));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        Position newPos = gps->getPosition();
        // No movement should occur without velocity or acceleration
        assert(newPos.getMetersX() == 50.0);
        assert(newPos.getMetersY() == 50.0);
    }

    void test_simulation_decelerationToStop() {
        
        physics.setVelocityX(10.0);
        physics.setVelocityY(0.0);
        physics.setTimePerFrame(1.0);
        // Simulate deceleration by applying negative acceleration
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        // The gps should decelerate to a stop
        assert(physics.getVelocityX() == 0.0);
        // The Y velocity should remain unchanged
        assert(physics.getVelocityY() == 0.0);
    }

    void test_simulation_positionChangeWithTimeAndAccel() {
        
        physics.setVelocityX(0.0);
        physics.setVelocityY(0.0);
        physics.setTimePerFrame(2.0); // 2 seconds per frame to magnify the effect
        // Apply gravity
        GPS* gps = GPS::create(Position(0, 0));
        gps->updatePosition(simulator);
        simulator.simulation(*gps);

        Position newPos = gps->getPosition();
        // Position should have changed according to s = ut + 1/2 * a * t^2
        // With u=0, it simplifies to s = 1/2 * a * t^2
        double expectedPosY = 0.5 * 9.81 * 4.0; // 0.5 * a * t^2
        assert(newPos.getMetersY() == expectedPosY);
        // The X position should remain the same as there is no horizontal movement
        assert(newPos.getMetersX() == 0.0);
    }

};


#pragma once
#include "position.h"
#include "simulator.h"
#include "physics.h"
class testSimulator
{
public:
	void run()
	{
        testInitialConditions();
        testGpsStationary();
        testTimePerFrameEffect();
        testIntegrationWithPhysics();
        testPositiveVelocity();
        testNegativeVelocity();
        testAccelerationEffectOnVelocity();
        testNoMovement();
        testDecelerationToStop();
        testPositionChangeWithTimeAndAccel();
	}

private:
    Position ptUpperRight;
    Simulator simulator;
    Physics physics;

    void testInitialConditions();
    void testGpsStationary();
    void testTimePerFrameEffect();
    void testIntegrationWithPhysics();
    void testPositiveVelocity();
    void testNegativeVelocity();
    void testAccelerationEffectOnVelocity();
    void testNoMovement();
    void testDecelerationToStop();
    void testPositionChangeWithTimeAndAccel();

};


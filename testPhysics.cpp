/***********************************************************************
 * Source File:
 *    Physics Test : Unit tests for Physics
 * Author:
 *    Spencer Sorenson
 * Summary:
 *    The unit tests for physics
 ************************************************************************/


#include "testPhysics.h"
#include <cassert>        // for ASSERT
#include <iostream>

void PhysicsTest::get_vx_positive()
{
	//setup
	double vx = 512.3;
	double test_vx;
	//exercise
	physics.setVelocityX(vx);
	test_vx = physics.getVelocityX();
	//verify
	assert(vx == test_vx);
}

void PhysicsTest::get_vx_negative()
{
	//setup
	double vx = -1512.3;
	double test_vx;
	//exercise
	physics.setVelocityX(vx);
	test_vx = physics.getVelocityX();
	//verify
	assert(vx == test_vx);
}

void PhysicsTest::get_vy_positive()
{
	//setup
	double vy = 512.3;
	double test_vy;
	//exercise
	physics.setVelocityX(vy);
	test_vy = physics.getVelocityX();
	//verify
	assert(vy == test_vy);
}

void PhysicsTest::get_vy_negative()
{
	//setup
	double vy = -1512.3;
	double test_vy;
	//exercise
	physics.setVelocityX(vy);
	test_vy = physics.getVelocityX();
	//verify
	assert(vy == test_vy);
}

void PhysicsTest::compute_g_normal()
{
	//setup
	double height = 1564;
	double expected = 9.801842236;
	//exercise
	result = physics.computeGravity(height);
	//verify
	assert(result == expected);
}

void PhysicsTest::h_above_earth_normal()
{
	//setup
	double x = 1546345;
	double y = 345323;
	double expected = 1584431.903;
	//exercise
	result = physics.heightAboveEarth(x, y);
	//verify
	assert(result == expected);
}

void PhysicsTest::direction_g_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_h_component_large()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_h_component_small()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_v_component_large()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_v_component_small()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::new_position_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_motion_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_h_pos_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_v_pos_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_distance_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_distance_invalid()
{
	//setup

	//exercise

	//verify

	//teardown

}

void PhysicsTest::compute_v_normal()
{
	//setup

	//exercise

	//verify

	//teardown

}

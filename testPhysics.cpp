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
	double xs = 3465326;
	double ys =-23462;
	double expected = 3.134822;
	//exercise
	result = physics.directionOfGravityPull(xs, ys);
	//verify
	assert(result == expected);
}

void PhysicsTest::compute_h_component_positive()
{
	//setup
	double a = 32;
	double angle = 1.23;
	double expected = 0.737161862;
	//exercise
	result = physics.computeHorizontalComponent(a, angle);
	//verify
	assert(result == expected);
}

void PhysicsTest::compute_h_component_negative()
{
	//setup
	double a = -32;
	double angle = 1.23;
	double expected = -0.737161862;
	//exercise
	result = physics.computeHorizontalComponent(a, angle);
	//verify
	assert(result == expected);
}

void PhysicsTest::compute_v_component_positive()
{
	//setup
	double a = 32;
	double angle = 1.23;
	double expected = 31.99150813;
	//exercise
	result = physics.computeVerticalComponent(a, angle);
	//verify
	assert(result == expected);
}

void PhysicsTest::compute_v_component_negative()
{
	//setup
	double a = -32;
	double angle = 1.23;
	double expected = -31.99150813;
	//exercise
	result = physics.computeVerticalComponent(a, angle);
	//verify
	assert(result == expected);
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

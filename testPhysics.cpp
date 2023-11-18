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
using namespace std;

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

	cout.setf(ios::left);
	cout.width(50);
	cout << "get_vx_positive";
	cout.width(10);
	cout << "passed" << endl;
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

	cout.setf(ios::left);
	cout.width(50);
	cout << "get_vx_negative";
	cout.width(10);
	cout << "passed" << endl;
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

	cout.setf(ios::left);
	cout.width(50);
	cout << "get_vy_positive";
	cout.width(10);
	cout << "passed" << endl;
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

	cout.setf(ios::left);
	cout.width(50);
	cout << "get_vy_negative";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_g_normal()
{
	//setup
	double height = 1564;
	double expected = 9.801842236;
	//exercise
	result = physics.computeGravity(height);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_g_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::h_above_earth_normal()
{
	//setup
	double x = 1546345.0;
	double y = 345232.0;
	double expected = -4793585.915;
	//exercise
	result = physics.heightAboveEarth(x, y);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "h_above_earth_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::direction_g_normal()
{
	//setup
	double xs = 3465326;
	double ys =-23462;
	double expected = -1.56402;
	//exercise
	result = physics.directionOfGravityPull(xs, ys);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "direction_g_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_h_component_positive()
{
	//setup
	double a = 32;
	double angle = 1.23;
	double expected = 30.15964;
	//exercise
	result = physics.computeHorizontalComponent(a, angle);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_h_component_positive";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_h_component_negative()
{
	//setup
	double a = -32;
	double angle = 1.23;
	double expected = -30.15964;
	//exercise
	result = physics.computeHorizontalComponent(a, angle);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_h_component_negative";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_v_component_positive()
{
	//setup
	double a = 32;
	double angle = 1.23;
	double expected = 10.69560;
	//exercise
	result = physics.computeVerticalComponent(a, angle);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_v_component_positive";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_v_component_negative()
{
	//setup
	double a = -32;
	double angle = 1.23;
	double expected = -10.69560;
	//exercise
	result = physics.computeVerticalComponent(a, angle);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_v_component_negative";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::new_position_normal()
{
	//setup
	double new_pos = 12345.123;
	double expected = 12345.123;
	//exercise
	result = physics.newPosition(new_pos);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "new_position_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_motion_normal()
{
	//setup
	double s0 = 123;
	double v = 1543;
	double t = 3.5;
	double expected = 5523.5;
	//exercise
	result = physics.computeMotion(s0, v, t);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_motion_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_h_pos_normal()
{
	//setup
	double x0 = 123;
	double dx = 1543;
	double t = 3.5;
	double expected = 5523.5;
	//exercise
	result = physics.computeHorizontalPosition(x0, dx, t);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_h_pos_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_v_pos_normal()
{
	//setup
	double y0 = 123;
	double dy = 1543;
	double t = 3.5;
	double expected = 5523.5;
	//exercise
	result = physics.computeVerticalPosition(y0, dy, t);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_v_pos_normal";
	cout.width(10);
	cout << "passed" << endl;
}

void PhysicsTest::compute_distance_normal()
{
	//setup
	double s0 = 123;
	double v = 1543;
	double t = 3.5;
	double a = -234;
	double expected = 4090.25;
	//exercise
	result = physics.computeDistance(s0, v, t, a);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_distance_normal";
	cout.width(10);
	cout << "passed" << endl;
}


void PhysicsTest::compute_v_normal()
{
	//setup
	double v0 = 123;
	double a = 1543;
	double t = 3.5;
	double expected = 5523.5;
	//exercise
	result = physics.computeVelocity(v0, a, t);
	//verify
	assert(fabs(result - expected) < EPSILON);

	cout.setf(ios::left);
	cout.width(50);
	cout << "compute_v_normal";
	cout.width(10);
	cout << "passed" << endl;
}

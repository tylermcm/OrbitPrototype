#pragma once
/***********************************************************************
 * Header File:
 *    Physics Test : Unit tests for physics
 * Author:
 *    Spencer Sorenson
 * Summary:
 *    The unit tests for physics
 ************************************************************************/

#pragma once
#include <set>

#include "physics.h"


/***************************************************
  * PHYSICS TEST
  * Test the physics class
  ***************************************************/
class PhysicsTest
{
public:
	double result;
	Physics physics;
	bool areEqual;

	void run()
	{
		//getters
		get_vx_positive();
		get_vx_negative();
		get_vy_positive();
		get_vy_negative();

		//computations
		compute_g_normal();
		h_above_earth_normal();
		direction_g_normal();
		compute_h_component_positive();
		compute_h_component_negative();
		compute_v_component_positive();
		compute_v_component_negative();
		new_position_normal();
		compute_motion_normal();
		compute_h_pos_normal();
		compute_v_pos_normal();
		compute_distance_normal();
		compute_v_normal();
	}

private:
	const double EPSILON = 0.001;

	//getters
	void get_vx_positive();
	void get_vx_negative();
	void get_vy_positive();
	void get_vy_negative();

	//computations
	void compute_g_normal();
	void h_above_earth_normal();
	void direction_g_normal();
	void compute_h_component_positive();
	void compute_h_component_negative();
	void compute_v_component_positive();
	void compute_v_component_negative();
	void new_position_normal();
	void compute_motion_normal();
	void compute_h_pos_normal();
	void compute_v_pos_normal();
	void compute_distance_normal();
	void compute_v_normal();
};

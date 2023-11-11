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
    bool result;
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
        compute_g_invalid();
        h_above_earth_normal();
        h_above_earth_negative();
        direction_g_normal();
        compute_h_component_large();
        compute_h_component_small();
        compute_v_component_large();
        compute_v_component_small();
        new_position_normal();
        compute_motion_normal();
        compute_h_pos_normal();
        compute_v_pos_normal();
        compute_distance_normal();
        compute_distance_invalid();
        compute_v_normal();
    }



private:
    //getters
    void get_vx_positive();
    void get_vx_negative();
    void get_vy_positive();
    void get_vy_negative();
    void get_TperF();
    void get_rot_speed();

    //computations
    void compute_g_normal();
    void compute_g_invalid();
    void h_above_earth_normal();
    void h_above_earth_negative();
    void direction_g_normal();
    void compute_h_component_large();
    void compute_h_component_small();
    void compute_v_component_large();
    void compute_v_component_small();
    void new_position_normal();
    void compute_motion_normal();
    void compute_h_pos_normal();
    void compute_v_pos_normal();
    void compute_distance_normal();
    void compute_distance_invalid();
    void compute_v_normal();
};


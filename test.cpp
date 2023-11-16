/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testPhysics.h"
#include "testSimulator.h"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
	cout << "Running position tests\n";
	TestPosition().run();
	cout << "Running physics tests\n";
    PhysicsTest().run();
	cout << "Running simulator tests\n";
	testSimulator().run();

	cout << "All tests passed";
}

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
	cout << "--------------------------------------------------------";
	cout << "\n\t\tRunning position tests" << endl;
	cout << "--------------------------------------------------------" << endl;
	TestPosition().run();

	cout << "--------------------------------------------------------";
	cout << "\n\t\tRunning physics tests" << endl;
	cout << "--------------------------------------------------------" << endl;
	PhysicsTest().run();

	cout << "--------------------------------------------------------";
	cout << "\n\t\tRunning simulator tests" << endl;
	cout << "--------------------------------------------------------" << endl;
	testSimulator().run();

	cout << "--------------------------------------------------------" << endl;
	cout << "All tests passed!";
}

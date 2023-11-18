#include <cassert>
#include <cmath>
#include "testSimulator.h"
#include "satellite.h"

void testSimulator::testGpsStartPosition()
{
	//setup
	GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, -3880.0, 0.0);
	Position newPos = gps->getPosition();

	//exercise
	sim.simulation(*gps);

	//verify
	assert(newPos.getMetersX() == 0.0);
	assert(newPos.getMetersY() == 26'560'000.0);

	//teardown
	delete gps;
}

void testSimulator::testGpsUpdatedPosition()
{
	//setup
	GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, -3880.0, 0.0);
	double expectedX = -186240.0;
	double expectedY = 26558045.63;

	//exercise
	gps->updatePosition(sim);
	Position updatedPos = gps->getPosition();

	//verify
	assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
	assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

	//teardown
	delete gps;
}

void testSimulator::testGpsPositiveXVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, 3880.0, 0.0);
    double expectedX = 186240.0;
    double expectedY = 26558045.63;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsPositiveYVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, 0.0, 4000.0);
    double expectedX = 0;
    double expectedY = 26750045.62;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsNegativeYVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, 0.0, -3500.0);
    double expectedX = 0;
    double expectedY = 26390045.62;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsNoVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, 0.0, 0.0);
    double expectedX = 0.0;
    double expectedY = 26'558'045.62; //position change due to gravity

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsEdgeXVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, 50'000.0, 0.0);
    double expectedX = 2'400'000.0;
    double expectedY = 26'558'045.62;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsEdgeYVelocity()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 26'560'000.0, -3880.0, 50'000.0);
    double expectedX = -186'240.0;
    double expectedY = 28'958'045.62;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsEdgePosY()
{
    //setup
    GPS* gps = GPS::create(pos, 0.0, 65'000'000.0, -3880.0, 0.0);
    double expectedX = -186'240.0;
    double expectedY = 64999673.68;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

void testSimulator::testGpsEdgePosXY()
{
    //setup
    GPS* gps = GPS::create(pos, -60'000'000.0, 60'000'000.0, -3880.0, 0.0);
    double expectedX = -60186104.6;
    double expectedY = 59999864.6;

    //exercise
    gps->updatePosition(sim);
    Position updatedPos = gps->getPosition();

    //verify
    assert(fabs(updatedPos.getMetersX() - expectedX) < EPSILON);
    assert(fabs(updatedPos.getMetersY() - expectedY) < EPSILON);

    //teardown
    delete gps;
}

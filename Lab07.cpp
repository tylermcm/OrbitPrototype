/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "physics.h"
#include "simulator.h"
#include "satellite.h"
#include "player.h"
#include "test.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
	Demo(Position ptUpperRight) : ptUpperRight(ptUpperRight), angleShip(4.71239), angleEarth(0.0) {
		// TODO We will eventually need to implement the other array of GPS we defined in satellite.cpp
		satellites.push_back(GPS::create(ptUpperRight, 0.0, 26'560'000.0, -3880.0, 0.0, 0.0));
		satellites.push_back(Hubble::create(ptUpperRight, 0.0, -42'164'000.0, 3100.0, 0.0, 0.0));
		satellites.push_back(Sputnik::create(ptUpperRight, -36'515'095.13, 21'082'000.0, 2050.0, 2684.68, 0.0));
		satellites.push_back(Starlink::create(ptUpperRight, 0.0, -13'020'000.0, 5800.0, 0.0, 0.0));
		satellites.push_back(Dragon::create(ptUpperRight, 0.0, 8'000'000.0, -7900.0, 0.0, 0.0));
		player = Player::create(0.0, 45'500'000.0, 0.0, -2000.0, 0.0);
		satellites.push_back(player);

	}


	Position ptGPS;
	Position ptUpperRight;
	Player* player;
	Physics physics;
	Simulator sim;
	double angleShip;
	double angleEarth;
	std::vector<Satellite*> satellites;
};


//I added all of the satellites to a vector which will make the collision detection easier.The code
//for that was provided in the lab video, so implementation should be straightforward.


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
	// Cast the void pointer into a Demo object
	Demo* pDemo = (Demo*)p;

	// Set up the drawing stream
	Position pt;
	ogstream gout(pt);

	// Handle player input and update player position
	pDemo->player->handleInput(pUI);
	//pDemo->player->updatePosition(pDemo->sim);

	// Rotate the earth
	pDemo->angleEarth += pDemo->physics.getRotationSpeed();
	for (auto satellite : pDemo->satellites)
		satellite->updatePosition(pDemo->sim);

	vector <Satellite*>::iterator satellite;
	vector <Satellite*>::iterator satellite2;
	// Update and draw each satellite
	for (satellite = pDemo->satellites.begin(); satellite != pDemo->satellites.end(); ++satellite)
		for ((satellite2 = satellite)++; satellite2 != pDemo->satellites.end(); ++satellite2)
			if (!(*satellite)->isDead() && !(*satellite2)->isDead())
			{
				double distance = computeDistance((*satellite)->getPosition(),
					                              (*satellite2)->getPosition());
				if (distance < (*satellite)->getRadius() + (*satellite2)->getRadius())
				{
					(*satellite)->kill();
					(*satellite2)->kill();
				}
			}
		
	for (auto satellite : pDemo->satellites)
		satellite->draw(gout, satellite->getAngle());

	// Draw the Player
	//pDemo->player->draw(gout, pDemo->player->getAngle());

	// Draw the earth
	pt.setMeters(0.0, 0.0);
	gout.drawEarth(pt, pDemo->angleEarth);
}


double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
	// Initialize OpenGL
	testRunner();
	Position ptUpperRight;
	ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
	ptUpperRight.setPixelsX(1000.0);
	ptUpperRight.setPixelsY(1000.0);
	Interface ui(0, NULL,
		"Demo",   /* name on the window */
		ptUpperRight);

	// Initialize the demo
	Demo demo(ptUpperRight);

	// set everything into action
	ui.run(callBack, &demo);


	return 0;
}


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
	Demo(Position ptUpperRight) :
		ptUpperRight(ptUpperRight)
		
	{
		angleShip = 4.71239;
		angleEarth = 0.0;
	}

	Position ptGPS;
	Position ptUpperRight;
	Satellite* GPS = GPS::create(ptUpperRight, 0.0, 26'560'000.0, -3880.0, 0.0);
	Satellite* Hubble = Hubble::create(ptUpperRight, 0.0, -42'164'000.0, 3100.0, 0.0);
	Satellite* Sputnik = Sputnik::create(ptUpperRight, -36'515'095.13, 21'082'000.0, 2050.0, 2684.68 );
	Satellite* Starlink = Starlink::create(ptUpperRight, 0.0, -13'020'000.0, 5800.0, 0.0);
	Satellite* Dragon = Dragon::create(ptUpperRight, 0.0, 8'000'000, -7900.0, 0.0);
	Player* Player = Player::create(0.0, 45'500'000.0, 0.0, -2000.0);
	Physics physics;
	Simulator sim;
	double angleShip;
	double angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
	// the first step is to cast the void pointer into a game object. This
	// is the first step of every single callback function in OpenGL. 
	Demo* pDemo = (Demo*)p;

	pDemo->Player->handleInput(pUI);

	// rotate the earth
	pDemo->angleEarth += pDemo->physics.getRotationSpeed();
    pDemo->angleShip += pDemo->physics.getRotationSpeed();
	pDemo->GPS->updatePosition(pDemo->sim);
	pDemo->Hubble->updatePosition(pDemo->sim);
	pDemo->Sputnik->updatePosition(pDemo->sim);
	pDemo->Starlink->updatePosition(pDemo->sim);
	pDemo->Dragon->updatePosition(pDemo->sim);
	pDemo->Player->updatePosition(pDemo->sim);
	


	//
	// draw everything
	//

	Position pt;
	ogstream gout(pt);
	pDemo->GPS->draw(gout, pDemo->angleShip);
	pDemo->Hubble->draw(gout, pDemo->angleShip);
	pDemo->Sputnik->draw(gout, pDemo->angleShip);
	pDemo->Starlink->draw(gout, pDemo->angleShip);
	pDemo->Dragon->draw(gout, pDemo->angleShip);
	pDemo->Player->draw(gout, pUI, pDemo->angleShip);



	// draw the earth
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


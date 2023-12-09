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
#include "earth.h"
#include "star.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
	Demo(Position ptUpperRight) : ptUpperRight(ptUpperRight), angleShip(4.71239), angleEarth(0.0)
	{
		//satellites.push_back(GPS::create(ptUpperRight, 0.0, 26'560'000.0, -3880.0, 0.0, 0.0));
		const auto& gpsData = Satellite::getGpsData();
		for (const auto& gpsVal : gpsData) {
			satellites.push_back(GPS::create(ptUpperRight, gpsVal.pos.getMetersX(), gpsVal.pos.getMetersY(), gpsVal.velX, gpsVal.velY, 0.0));
		}

		for (int i = 0; i < 500; i++)
		{
			// screen is 1,000 x 1,000 pixels.
			Position initial;
			initial.setPixelsX(random(-500, 500));
			initial.setPixelsY(random(-500, 500));

			this->stars.push_back(new Star(initial));
		}

		satellites.push_back(Hubble::create(ptUpperRight, 0.0, -42'164'000.0, 3100.0, 0.0, 0.0));
		satellites.push_back(Sputnik::create(ptUpperRight, -36'515'095.13, 21'082'000.0, 2050.0, 2684.68, 0.0));
		satellites.push_back(Starlink::create(ptUpperRight, 0.0, -13'020'000.0, 5800.0, 0.0, 0.0));
		satellites.push_back(Dragon::create(ptUpperRight, 0.0, 8'000'000.0, -7900.0, 0.0, 0.0));
		player = Player::create(0.0, 45'500'000.0, 0.0, -2000.0, 0.0);
		satellites.push_back(player);
		satellites.push_back(new Earth());
	}


	Position ptGPS;
	Position ptUpperRight;
	Player* player;
	Physics physics;
	Simulator sim;
	double angleShip;
	double angleEarth;
	std::vector<Satellite*> satellites;
	std::vector<Star*> stars;


	
	void handlePlayerInput(const Interface* pUI) {
		if (!player->isDead()) {
			player->handleInput(pUI);
			if (pUI->isSpace()) {
				Projectile* newProjectile = player->shoot();
 				satellites.push_back(newProjectile);
			}
		}
	}

	void updateSatellites(double elapsedTime) {
		for (auto satellite : satellites) {
			Projectile* projectile = dynamic_cast<Projectile*>(satellite);
			if (projectile != nullptr) {
				projectile->update(elapsedTime, 1.0 / 30.0);
			}
			else {
				satellite->updatePosition(sim);
			}
		}
	}

	void checkCollisions() {
		for (auto it1 = satellites.begin(); it1 != satellites.end(); ++it1) {
			for (auto it2 = std::next(it1); it2 != satellites.end(); ++it2) {
				if (!(*it1)->isDead() && !(*it2)->isDead()) {
					double distance = computeDistance((*it1)->getPosition(), (*it2)->getPosition()) / 128000;
					if (distance < (*it1)->getRadius() + (*it2)->getRadius()) {
						(*it1)->kill();
						(*it2)->kill();
					}
				}
			}
		}
	}

	void drawSatellites(ogstream& gout) {
		for (auto satellite : satellites) {
			satellite->draw(gout, satellite->getAngle());
		}
		std::cout << satellites.size() << std::endl;
	}

	void drawStars(ogstream& gout) {
		for (auto star : stars)
			star->draw(gout, star->getAngle());
	}
	void removeDeadSatellites()
	{
		for (auto it = satellites.begin(); it != satellites.end();)
		{
			if ((*it)->isDead())
			{
				delete*it; // Free the memory
				it = satellites.erase(it);
			}
			else
			{
				++it; 
			}
		}
	}
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
	// Cast the void pointer into a Demo object
	auto pDemo = static_cast<Demo*>(p);

	// Set up the drawing stream
	Position pt;
	ogstream gout(pt);
	pDemo->angleEarth += pDemo->physics.getRotationSpeed();


	pDemo->handlePlayerInput(pUI);
	pDemo->updateSatellites(48.0);
	pDemo->checkCollisions();
	pDemo->removeDeadSatellites();
	pDemo->drawSatellites(gout);
	pDemo->drawStars(gout);

	pt.setMeters(0.0, 0.0);
	
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
	Interface ui(0, nullptr,
	             "Demo", /* name on the window */
	             ptUpperRight);

	// Initialize the demo
	Demo demo(ptUpperRight);

	// set everything into action
	ui.run(callBack, &demo);


	return 0;
}

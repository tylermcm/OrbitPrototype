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
#define _USE_MATH_DEFINES
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include <cmath>
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

	  ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      ptGPS.setMeters(0.0, 42164000);

	  angleShip = 4.71239;
	  angleEarth = 0.0;
	}

	Position ptGPS;
	Position ptUpperRight;


	double angleShip;
	double angleEarth;
    double velocityX = -3100.0;
    double velocityY = 0.0;
	double timeDilation = 24 * 60;
	double timePerFrame = timeDilation / 30;
	double rotationSpeed = -(2 * M_PI / 30) * (timeDilation / 86400);

    // Function to compute the magnitude of acceleration due to gravity at an altitude (h)
    double computeGravity(double h) const {
        const double g = 9.80665; // gravity at sea level in m/s^2
        const double r = 6378000; // radius of the Earth in meters

        double gh = g * pow((r / (r + h)), 2);
        return gh;
    }

    // Function to compute the height above the Earth in meters
    double heightAboveEarth(double x, double y) const {
        const double r = 6378000; // radius of the Earth in meters

        double h = sqrt(pow(x, 2) + pow(y, 2)) - r;
        return h;
    }

    // Function to compute the direction of the pull of gravity in radians
    double directionOfGravityPull(double xs, double ys) const {
        const double xe = 0; 
        const double ye = 0; 

        double d = atan2(xe - xs, ye - ys);
        return d;
    }

    // Function to compute the horizontal component of acceleration
    double computeHorizontalComponent(double a, double angle) const {
        double ddx = a * sin(angle);
        return ddx;
    }

    // Function to compute the vertical component of acceleration
    double computeVerticalComponent(double a, double angle) const {
        double ddy = a * cos(angle);
        return ddy;
    }
    // Newton's first law: st = s0
    double newPosition(double s0) {
        return s0;
    }

    // Motion with constant velocity: s = s0 + v * t
    double computeMotion(double s0, double v, double t) {
        return s0 + v * t;
    }

    // Horizontal position with constant velocity: xt = x0 + dx * t
    double computeHorizontalPosition(double x0, double dx, double t) {
        return x0 + dx * t;
    }

    // Vertical position with constant velocity: yt = y0 + dy * t
    double computeVerticalPosition(double y0, double dy, double t) {
        return y0 + dy * t;
    }

    // Distance formula with acceleration: s = s0 + v * t + 0.5 * a * t^2
    double computeDistance(double s0, double v, double t, double a) {
        return s0 + v * t + 0.5 * a * std::pow(t, 2);
    }

    // Velocity with constant acceleration: v = v0 + a * t
    double computeVelocity(double v0, double a, double t) {
        return v0 + a * t;
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
	// the first step is to cast the void pointer into a game object. This
	// is the first step of every single callback function in OpenGL. 
	Demo* pDemo = (Demo*)p;



	// rotate the earth
	pDemo->angleEarth += pDemo->rotationSpeed;
    pDemo->angleShip += pDemo->rotationSpeed;
	//
	// draw everything
	//

	Position pt;
	ogstream gout(pt);

    double acceleration = pDemo->computeGravity(pDemo->heightAboveEarth(pDemo->ptGPS.getMetersX(), pDemo->ptGPS.getMetersY()));
    double angle = pDemo->directionOfGravityPull(pDemo->ptGPS.getMetersX(), pDemo->ptGPS.getMetersY());

    // Compute the components of acceleration
    double ddx = pDemo->computeHorizontalComponent(acceleration, angle);
    double ddy = pDemo->computeVerticalComponent(acceleration, angle);

    // Update the velocity based on the acceleration
    pDemo->velocityX += ddx * pDemo->timePerFrame;
    pDemo->velocityY += ddy * pDemo->timePerFrame;

    // Update the position based on the new velocity
    double newPosX = pDemo->computeDistance(pDemo->ptGPS.getMetersX(), pDemo->velocityX, pDemo->timePerFrame, ddx);
    double newPosY = pDemo->computeDistance(pDemo->ptGPS.getMetersY(), pDemo->velocityY, pDemo->timePerFrame, ddy);

    // Set the new position
    pDemo->ptGPS.setMeters(newPosX, newPosY);	// draw satellites
	gout.drawGPS       (pDemo->ptGPS,        pDemo->angleShip);


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

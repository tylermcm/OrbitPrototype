#pragma once
#include "element.h"
#include "uiDraw.h"

const int STAR_PHASE_LIMIT = 250; // The max star phase

/*********************************************
 * Star
 * A star that exists in space. It is part of the background
 * so it has no collision and is not affected by Earth's gravity.
 *********************************************/
class Star : public Element
{
public:
    Star(const Position& pos)
    {
        this->position = pos;
        this->phase = random(0, STAR_PHASE_LIMIT); /* Start at a random phase */
    };

    /******************************************
    * UPDATE
    * Stars don't need their position or velocity updated,
    * so only their phase is updated
    ********************************************/
    void update(double time) {
        if (phase > STAR_PHASE_LIMIT)
            this->phase = 0; // Resets phase to 0, as to not increment infinitely
        else
            this->phase++; // Increment phase
    };

    void draw(ogstream& gout, double angle) {
        gout.drawStar(position, angle);
    }

   void updatePosition(Simulator& sim) override
   {

   }

   void kill() override
   {

   }
    /******************************************
    * GET PHASE
    * Returns the Star's current phase
    ********************************************/
    int getPhase() { return this->phase; };

private:
    int phase;  // The current phase of the Star, used to draw a Star differently
};

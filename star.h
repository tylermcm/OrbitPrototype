#pragma once
#include "element.h"
#include "uiDraw.h"

const int STAR_PHASE_LIMIT = 250; // The max star phase

class Star : public Element
{
public:
    Star(const Position& pos)
    {
        this->position = pos;
        this->phase = random(0, STAR_PHASE_LIMIT); /* Start at a random phase */
    };

    void update() {
        if (phase > STAR_PHASE_LIMIT)
            this->phase = 0; // Resets phase to 0 once it reaches star phase limit
        else
            this->phase++; // Increment phase
    };

    void draw(ogstream& gout, double phase) {
        gout.drawStar(position, phase);
    }

   void updatePosition(Simulator& sim) override
   {

   }

   void kill() override
   {

   }

    int getPhase() { return this->phase; };

private:
    int phase;  // The current phase of the Star, used to draw a Star differently
};

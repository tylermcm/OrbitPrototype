#pragma once
#include "position.h"
#include "simulator.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Player : public Element
{
public:
    Player(const Position& pos, double velX, double velY, double angle) : Element(pos, velX, velY, angle) {}

    static Player* create(double posX, double posY, double velX, double velY, double angle)
    {
        Position initialPos = setInitialPosition(posX, posY);
        Player* newPlayer = new Player(initialPos, velX, velY, angle);
        newPlayer->setInitialVelocity(velX, velY);
        return newPlayer;
    }

    static Position setInitialPosition(double posX, double posY)
    {
        Position initialPos;
        initialPos.setMeters(posX, posY);
        return initialPos;
    }

    void updatePosition(Simulator& sim) override
    {
        sim.simulation(*this);
    }

    void draw(ogstream& gout, const Interface* pUI, double angle) const
    {
        gout.drawShip(this->getPosition(), angle, pUI->isSpace());
    }

    void handleInput(const Interface* pUI)
    {
        if (pUI->isDown())
            this->position.addPixelsY(-1.0);
        if (pUI->isLeft())
            this->angle -= 0.1;
        if (pUI->isRight())
            this->angle += 0.1;
    }

};

#pragma once
#include "position.h"
#include "simulator.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Player : public Element
{
public:
    Player(const Position& pos) : Element(pos) {}

    static Player* create(double posX, double posY, double velX, double velY)
    {
        Position initialPos = setInitialPosition(posX, posY);
        Player* newPlayer = new Player(initialPos);
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
        if (pUI->isUp())
            this->position.addPixelsY(1.0);
        if (pUI->isDown())
            this->position.addPixelsY(-1.0);
        if (pUI->isLeft())
            this->position.addPixelsX(-1.0);
        if (pUI->isRight())
            this->position.addPixelsX(1.0);
    }

};

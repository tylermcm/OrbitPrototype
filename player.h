#pragma once
#include <vector>
#include "projectile.h"
#include "position.h"
#include "simulator.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "satellite.h"


class Player : public Satellite
{
public:
    Player(const Position& pos, double velX, double velY, double angle)
		: Satellite(pos, velX, velY, angle) 
    {
        this->dead = false;
        this->radius = 10;
        this->numFragments = 4;
        this->thrust = false;
    }

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
        updateProjectiles(48.0, 1.0 / 30.0);
    }

    void kill() override
    {
        this->dead = true;
    }

    void setThrust(bool t)
    {
        this->thrust = t;
    }

    void draw(ogstream& gout, double angle) 
    {
        drawProjectiles(gout);
        gout.drawShip(this->getPosition(), angle, this->thrust);
        std::cout << "ship angle: " << angle << std::endl;
        
    }

    void handleInput(const Interface* pUI)
    {
        if (pUI->isDown())
        {
            physics.setDDX(physics.computeHorizontalComponent(2.0, angle));
            physics.setDDY(physics.computeVerticalComponent(2.0, angle));

            physics.setVelocityX(physics.computeVelocity(physics.getVelocityX(), physics.getDDX(), 48));
            physics.setVelocityY(physics.computeVelocity(physics.getVelocityY(), physics.getDDY(), 48));

        }
        if (pUI->isLeft())
            this->angle -= 0.1;
        if (pUI->isRight())
            this->angle += 0.1;
        if (pUI->isSpace())
        {
             shoot();
        }
    }

    void shoot() {
        Position playerPos = getPosition();
        double shootAngle = getAngle();

        Position projectileStart = rotate(playerPos, 0.0, 19.0, shootAngle);
        double additionalVelocity = 9000;

        projectiles.emplace_back(projectileStart, shootAngle, additionalVelocity);
    }

    void updateProjectiles(double elapsedTime, double realTimeElapsed) {
        for (auto& projectile : projectiles) {
            projectile.update(elapsedTime, realTimeElapsed);
        }
    }

    void drawProjectiles(ogstream& gout) {
        for (auto& projectile : projectiles) {
            if (projectile.isActive()) {
                gout.drawProjectile(projectile.getPosition());
            }
        }
    }



private:
    Projectile projectile;
    std::vector<Projectile> projectiles;
    bool thrust;
};







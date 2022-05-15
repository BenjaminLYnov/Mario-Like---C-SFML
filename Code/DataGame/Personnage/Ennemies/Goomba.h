#ifndef GOOMBA_H
#define GOOMBA_H

#pragma once

#include "../../Actor/Actor.h"

class Goomba : public Actor
{
public:
    Goomba();
    Goomba(std::vector<sf::Vector2f> pos);
    Goomba(float speedMove, std::vector<sf::Vector2f> pos);
    Goomba(float speedMove, float gravityForce, std::vector<sf::Vector2f> pos);
    ~Goomba();

    void performMovement(float deltaTime);

protected:
    void init();
    void animationMove(float deltaTime);
    void initRect();
    float timerAnimation = 0;
    sf::IntRect rec[2][8];

    int indexX = 0;
    int indexY = 0;
};

#endif
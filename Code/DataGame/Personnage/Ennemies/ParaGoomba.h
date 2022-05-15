#ifndef PARAGOOMBA_H
#define PARAGOOMBA_H

#pragma once


#include "../../Actor/Actor.h"

class ParaGoomba :  public Actor
{
public:
    ParaGoomba();
    ParaGoomba(std::vector<sf::Vector2f> pos);
    ParaGoomba(float speedMove, std::vector<sf::Vector2f> pos);

    ~ParaGoomba();

    void performMovement(float deltaTime);


private:
    void init();
    void animationMove(float deltaTime);
    void initRect();
    float timerAnimation = 0;
    sf::IntRect rec[5];

    int indexX = 0;
};

#endif
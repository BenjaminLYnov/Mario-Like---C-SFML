#ifndef REX_H
#define REX_H

#pragma once

#include "../../Actor/Actor.h"

class Rex : public Actor
{
public:
    Rex();
    Rex(std::vector<sf::Vector2f> pos);
    Rex(float speedMove, std::vector<sf::Vector2f> pos);
    ~Rex();

    void performMovement(float deltaTime);

private:
void init();
    void animationMove(float deltaTime);
    void initRect();
    float timerAnimation = 0;
    sf::IntRect rec[2][2];

    int indexX = 0;
    int indexY = 0;

    bool wapaproundLeft = true;
    bool wapaproundRight = false;
};

#endif
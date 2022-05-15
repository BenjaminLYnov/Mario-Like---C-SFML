#ifndef SHROOM_H
#define SHROOM_H

#include "../Actor/Actor.h"

#pragma once

class Shroom : public Actor
{
public:
    Shroom();
    Shroom(int posX, int posY);
    ~Shroom();

    void performMovement(float deltaTime);
    void changeDirection();

private:
    bool directionLeft;
};

#endif
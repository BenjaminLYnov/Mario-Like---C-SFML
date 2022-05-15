#include "Shroom.h"

Shroom::Shroom()
{
    sprite = new SfmlImage("ressources/Images/Super_Mushroom_-_2D_shaded.png", 602, 600, 500, 500);
    sprite->getSprite().setScale(0.03, 0.03);
    directionLeft = false;
    speedMove = 0.06;
}

Shroom::Shroom(int posX, int posY)
{
    sprite = new SfmlImage("ressources/Images/Super_Mushroom_-_2D_shaded.png", 602, 600, posX, posY);
    sprite->getSprite().setScale(0.03, 0.03);
    directionLeft = false;
    speedMove = 0.06;
}

Shroom::~Shroom()
{
}

void Shroom::performMovement(float deltaTime)
{
    float xMov = 0;

    if (directionLeft)
        xMov = -1;
    else
        xMov = 1;

    sprite->getSprite().move(xMov * speedMove * deltaTime, 0);
    gravity(deltaTime);
}

void Shroom::changeDirection()
{
    directionLeft = !directionLeft;
}

#include "Actor.h"

Actor::Actor()
{
    wayPoint = WayPoint();
}

Actor::~Actor()
{
    // delete sprite;
}

void Actor::draw(sf::RenderWindow &window) const
{
    sprite->draw(window);
}

void Actor::gravity(float deltaTime)
{
    if (isOnGround)
        gravitySpeed = 0;
    else
        gravitySpeed += gravityForce;

    sprite->getSprite().move(0, gravitySpeed * deltaTime);
}
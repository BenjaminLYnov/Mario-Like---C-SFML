#include "WayPoint.h"
#include "iostream"
#include "../Math/Vector2D.hpp"

WayPoint::WayPoint()
{
}

WayPoint::~WayPoint()
{
}

void WayPoint::addPoint(sf::Vector2f point)
{
    wayPoints.push_back(point);
}

void WayPoint::followPoint(sf::Sprite &sprite, float speedMove)
{
    if (Vector2D::Distance(sprite.getPosition(), wayPoints[targetPoint]) <= 10)
    {
        targetPoint++;
        targetPoint %= wayPoints.size();
    }

    // Determine direction
    sf::Vector2f dir = wayPoints[targetPoint] - sprite.getPosition();
    dir = Vector2D::Normalized(dir);

    // Move sprite with the direction obtaint
    sprite.move(dir * speedMove);
}

sf::Vector2f WayPoint::getVectorDirectionPoint(sf::Vector2f spritePosition)
{
    if (Vector2D::Distance(spritePosition, wayPoints[targetPoint]) <= 30)
    {
        targetPoint++;
        targetPoint %= wayPoints.size();
    }

    // Determine direction
    sf::Vector2f dir = wayPoints[targetPoint] - spritePosition;

    if (!(dir.x == 0 && dir.y == 0))
        dir = Vector2D::Normalized(dir);


    return dir;
}

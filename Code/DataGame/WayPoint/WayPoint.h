#ifndef WAYPOINT_H
#define WAYPOINT_H

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class WayPoint
{
public:
    WayPoint();
    ~WayPoint();

    sf::Vector2f getVectorDirectionPoint(sf::Vector2f spritePosition);

    void followPoint(sf::Sprite &sprite, float speedMove);
    void addPoint(sf::Vector2f point);

// protected:
    std::vector<sf::Vector2f> wayPoints;
    int targetPoint = 0;
};

#endif
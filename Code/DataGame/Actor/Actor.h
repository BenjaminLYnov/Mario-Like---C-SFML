#ifndef ACTOR_H
#define ACTOR_H

#pragma once

#include "../SFML/SfmlAudio.hpp"
#include "../SFML/SfmlImage.hpp"
#include "../WayPoint/WayPoint.h"
#include <vector>

class Actor
{
public:
    Actor();
    ~Actor();

    bool isOnGround = false;
    float speedMove = 0.1;
    int hp = 1;
    bool deathLeft = true;
    SfmlImage *sprite;

    void draw(sf::RenderWindow &window) const;

    void gravity(float deltaTime);

protected:
    float gravitySpeed = 0;
    float gravityForce = 0.03;
    float jumpSpeed = 1;
    WayPoint wayPoint;

private:
};

#endif
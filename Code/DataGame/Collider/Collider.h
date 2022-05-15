#ifndef COLLIDER_H
#define COLLIDER_H

#pragma once
#include "Box.h"

#define NBR_COLLIDER 26

enum CollisionType
{
    All,
    Up,
    Down,
    Left,
    Right,
    Foot
};

class Collider
{
public:
    Collider();
    ~Collider();

    void draw(sf::RenderWindow &window) const;
    void notTrigger(sf::Sprite &sprite);
    sf::Sprite &getSprite(int index) const;
    
private:
    Box box[NBR_COLLIDER];

    void initBox();
    void setBox(int index, int posX, int posY, float scaleX, float scaleY, float rotation, int collisionType);
};

#endif
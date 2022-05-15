#ifndef BOX_H
#define BOX_H

#pragma once

#include "../SFML/SfmlImage.hpp"

class Box
{
public:
    Box();
    ~Box();

    void draw(sf::RenderWindow &window) const;
    sf::Sprite &getSprite() const;

    int collisionType;

private:
	SfmlImage *hitbox;
};

#endif
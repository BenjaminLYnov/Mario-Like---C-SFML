#include "Box.h"

Box::Box()
{
    hitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 300, 500);
    hitbox->SetCentralOrigin();
    hitbox->getSprite().setColor(sf::Color(12, 23, 56));

    collisionType = 0;
}

Box::~Box()
{
    delete hitbox;
}

sf::Sprite &Box::getSprite() const
{
    return hitbox->getSprite();
}

void Box::draw(sf::RenderWindow &window) const
{
    hitbox->draw(window);
}
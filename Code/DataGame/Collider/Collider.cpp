#include "Collider.h"
#include "../Collision/Collision.h"

#include "iostream"

Collider::Collider()
{
    initBox();
}

Collider::~Collider()
{
}

// Public Functions

sf::Sprite &Collider::getSprite(int index) const
{
    return box[index].getSprite();
}

void Collider::notTrigger(sf::Sprite &sprite)
{
    for (int i = 0; i < NBR_COLLIDER; i++)
    {
        if (box[i].collisionType == All)
            Collision::NotTrigger(sprite, box[i].getSprite());
        else if (box[i].collisionType == Up)
            Collision::NotTriggerBySide("Up", sprite, box[i].getSprite());
        else if (box[i].collisionType == Left)
            Collision::NotTriggerBySide("Left", sprite, box[i].getSprite());
        else if (box[i].collisionType == Down)
            Collision::NotTriggerBySide("Down", sprite, box[i].getSprite());
        else if (box[i].collisionType == Right)
            Collision::NotTriggerBySide("Right", sprite, box[i].getSprite());
        else if (box[i].collisionType == Foot)
            Collision::NotTriggerBySide("Foot", sprite, box[i].getSprite());
    }
}

void Collider::draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < NBR_COLLIDER; i++)
        box[i].draw(window);
}

// Private Functions

void Collider::initBox()
{
    setBox(0, 0, 1378, 3, 3, 0, All);
    setBox(1, 484, 1378, 5.5, 3, 0, All);
    setBox(2, 1136, 1378, 0.3, 3, 0, All);
    setBox(3, 1265, 1378, 0.3, 3, 0, All);
    setBox(4, 1378, 1378, 7.77, 3, 0, All);
    setBox(5, 1777, 1298, 0.78, 3, 0, All);
    setBox(6, 1855, 1328, 1.1, 3, 0, All);
    setBox(7, 2290, 1378, 8.1, 3, 0, All);
    setBox(8, 3250, 1363, 5.57, 3, 0, All);
    setBox(9, 4338, 1378, 5.2, 3, 0, All);
    setBox(10, 4977, 1378, 1.56, 3, 0, All);
    setBox(11, 5217, 1378, 3.3, 3, 0, All);
    setBox(12, 5650, 1346, 1.08, 3, 0, All);
    setBox(13, 5873, 1282, 0.93, 3, 0, All);
    setBox(14, 6081, 1170, 0.93, 4, 0, All);
    setBox(15, 6338, 1378, 4.3, 3, 0, All);
    setBox(16, 6930, 1250, 2.52, 4, 0, All);
    setBox(17, 7182, 1378, 25.1, 3, 0, All);
    setBox(18, 7450, 1234, 1.4, 0.1, 0, All);
    setBox(19, 7625, 1089, 1.42, 0.1, 0, All);
    setBox(20, 7817, 1234, 1.42, 0.1, 0, All);
    setBox(21, 8040, 1089, 1.42, 0.1, 0, All);
    setBox(22, 8040, 1234, 1.42, 0.1, 0, All);
    setBox(23, 8409, 1234, 9.58, 0.1, 0, All);
    setBox(24, 8569, 1089, 5.75, 0.1, 0, All);
    setBox(25, 11778, 1380, 100, 3, 0, All);
}

void Collider::setBox(int index, int posX, int posY, float scaleX, float scaleY, float rotation, int collisionType)
{
    box[index].getSprite().setRotation(rotation);
    box[index].getSprite().setScale(scaleX, scaleY);
    box[index].getSprite().setPosition(posX + box[index].getSprite().getTextureRect().width / 2 * box[index].getSprite().getScale().x, posY + box[index].getSprite().getTextureRect().height / 2 * box[index].getSprite().getScale().y);
    box[index].collisionType = collisionType;
}

#include "Radius.hpp"
#include "iostream"
#include "Vector2D.hpp"

Radius::Radius()
{
}

Radius::~Radius()
{
}

float Radius::dot(sf::Sprite sprite1, sf::Sprite sprite2)
{

     // double sprite1OriginX = sprite1.getPosition().x + sprite1.getTextureRect().width * sprite1.getScale().x / 2;
     // double sprite1OriginY = sprite1.getPosition().y + sprite1.getTextureRect().height * sprite1.getScale().y / 2;
     // double sprite2OriginX = sprite2.getPosition().x + sprite2.getTextureRect().width * sprite2.getScale().x / 2;
     // double sprite2OriginY = sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2;
     // double rayon = sqrt(pow(sprite1OriginX - sprite2OriginX, 2) + pow(sprite1OriginY - sprite2OriginY, 2));
     // double coteOppose = sqrt(pow(sprite1OriginX - (sprite2OriginX + rayon), 2) + pow(sprite1OriginY - sprite2OriginY, 2));
     // double radius = acos(((0.5) * (2 * pow(rayon, 2) - pow(coteOppose, 2))) / pow(rayon, 2)) * 180 / PI;
     // if (sprite1OriginY > sprite2OriginY)
     //      radius = -radius;

     sprite1.setOrigin(sprite1.getTextureRect().width * abs(sprite1.getScale().x) / 2, sprite1.getTextureRect().height * abs(sprite1.getScale().y) / 2);
     sprite2.setOrigin(sprite2.getTextureRect().width * abs(sprite2.getScale().x) / 2, sprite2.getTextureRect().height * abs(sprite2.getScale().y) / 2);
     float rayon = Vector2D::Distance(sprite1.getPosition(), sprite2.getPosition());
     float coteOppose = sqrt(pow(sprite1.getPosition().x - (sprite2.getPosition().x + rayon), 2) + pow(sprite1.getPosition().y - sprite2.getPosition().y, 2));
     float radius = acos(((0.5) * (2 * pow(rayon, 2) - pow(coteOppose, 2))) / pow(rayon, 2)) * 180 / PI;

     if (sprite1.getPosition().y > sprite2.getPosition().y)
          radius = -radius;
     // return 4;
     return radius;
}

double Radius::radiusBeetween2Sprites(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     double sprite1OriginX = sprite1.getPosition().x + sprite1.getTextureRect().width * sprite1.getScale().x / 2;
     double sprite1OriginY = sprite1.getPosition().y + sprite1.getTextureRect().height * sprite1.getScale().y / 2;
     double sprite2OriginX = sprite2.getPosition().x + sprite2.getTextureRect().width * sprite2.getScale().x / 2;
     double sprite2OriginY = sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2;
     double rayon = sqrt(pow(sprite1OriginX - sprite2OriginX, 2) + pow(sprite1OriginY - sprite2OriginY, 2));
     double coteOppose = sqrt(pow(sprite1OriginX - (sprite2OriginX + rayon), 2) + pow(sprite1OriginY - sprite2OriginY, 2));
     double radius = acos(((0.5) * (2 * pow(rayon, 2) - pow(coteOppose, 2))) / pow(rayon, 2)) * 180 / PI;
     if (sprite1OriginY > sprite2OriginY)
          radius = -radius;
     return radius;
}

double Radius::distanceBeetween2Sprites(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     double sprite1OriginX = sprite1.getPosition().x + sprite1.getTextureRect().width * sprite1.getScale().x / 2;
     double sprite1OriginY = sprite1.getPosition().y + sprite1.getTextureRect().height * sprite1.getScale().y / 2;
     double sprite2OriginX = sprite2.getPosition().x + sprite2.getTextureRect().width * sprite2.getScale().x / 2;
     double sprite2OriginY = sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2;
     double rayon = sqrt(pow(sprite1OriginX - sprite2OriginX, 2) + pow(sprite1OriginY - sprite2OriginY, 2));
     return rayon;
}

double Radius::radiusBeetween2Vector(double vec1X, double vec1Y, double vec2X, double vec2Y)
{
     double rayon = sqrt(pow(vec1X - vec2X, 2) + pow(vec1Y - vec2Y, 2));
     double coteOppose = sqrt(pow(vec1X + rayon - vec2X, 2) + pow(vec1Y - vec2Y, 2));
     double radius = acos(((0.5) * (2 * pow(rayon, 2) - pow(coteOppose, 2))) / pow(rayon, 2)) * 180 / PI;
     if (vec1Y < vec2Y)
          radius = 360 - radius;
     return radius;
}

double Radius::radiusCorner(sf::Sprite &sprite)
{
     double originX = sprite.getPosition().x + sprite.getTextureRect().width * sprite.getScale().x / 2;
     double originY = sprite.getPosition().y + sprite.getTextureRect().height * sprite.getScale().y / 2;
     double cornerX = sprite.getPosition().x + sprite.getTextureRect().width * sprite.getScale().x;
     double cornerY = sprite.getPosition().y;
     double hypotenuse = sqrt(pow(originX - cornerX, 2) + pow(originY - cornerY, 2));
     double coteOppose = sqrt(pow(originY - cornerY, 2));
     double radius = acos(((0.5) * (pow(sprite.getTextureRect().width * sprite.getScale().x / 2, 2) + pow(hypotenuse, 2) - pow(coteOppose, 2))) / (hypotenuse * sprite.getTextureRect().width * sprite.getScale().x / 2)) * 180 / PI;
     return radius;
}

sf::Sprite *Radius::mostNear(sf::Sprite &spriteOrigin, sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (distanceBeetween2Sprites(spriteOrigin, sprite2) <= distanceBeetween2Sprites(spriteOrigin, sprite1))
          return &sprite2;
     else
          return &sprite1;
}

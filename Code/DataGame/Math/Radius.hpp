#ifndef RADIUS_H
#define RADIUS_H
#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

class Radius
{
private:
public:
	Radius();
	~Radius();
	static float dot(sf::Sprite sprite1, sf::Sprite sprite2);
	static double distanceBeetween2Sprites(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static double radiusBeetween2Sprites(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static double radiusBeetween2Vector(double vec1X, double vec1Y, double vec2X, double vec2Y);
	static double radiusCorner(sf::Sprite &sprite);
	static sf::Sprite *mostNear(sf::Sprite &spriteOrigin, sf::Sprite &sprite1, sf::Sprite &sprite2);
};
#endif
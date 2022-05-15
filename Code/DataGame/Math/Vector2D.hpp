#ifndef VECTOR2D_H
#define VECTOR2D_H
#pragma once

#include <SFML/System/Vector2.hpp>

#define PI 3.14159265358979323846

class Vector2D
{
private:
public:
	Vector2D();
	~Vector2D();

	static float Distance(sf::Vector2f vec1, sf::Vector2f vec2);
	static sf::Vector2f Normalized(sf::Vector2f vec);
};
#endif
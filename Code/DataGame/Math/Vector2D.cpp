#include "Vector2D.hpp"
#include <math.h>
	
Vector2D::Vector2D()
{
	
}
	
Vector2D::~Vector2D()
{
	
}

float Vector2D::Distance(sf::Vector2f vec1, sf::Vector2f vec2) 
{
	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}

sf::Vector2f Vector2D::Normalized(sf::Vector2f vec) 
{
    sf::Vector2f vecNormalized;
    float norme = sqrt(vec.x * vec.x + vec.y * vec.y);
    vecNormalized.x = vec.x / norme;
    vecNormalized.y = vec.y / norme;
	return vecNormalized;
}

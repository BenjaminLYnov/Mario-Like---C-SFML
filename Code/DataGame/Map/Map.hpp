#ifndef MAP_H
#define MAP_H
#pragma once

#include "TileMap.hpp"
#include "../SFML/SfmlImage.hpp"

enum BackgroundSide {
	LEFT,
	RIGHT, 
	MIDDLE
};

class Map
{

public:
	Map();
	~Map();

	void Draw(sf::RenderWindow &window) const;

	void moveBackgroundParallax(sf::Vector2f viewPosition);

private:
	TileMap *ground;
	TileMap *props;

	SfmlImage *background[3];
	SfmlImage *farground[3];

	float backgroundSpeed = 0.8;
	float fargroundSpeed = 0.9;

	sf::Vector2f previousViewPosition = sf::Vector2f(0, 0);

	bool isInit = true;

	void movePlan(SfmlImage *planMiddle, SfmlImage *planLeft, SfmlImage *planRight, sf::Vector2f viewPosition, float moveSpeed);
};
#endif
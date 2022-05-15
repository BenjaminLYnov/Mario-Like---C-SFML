#ifndef GAMEOVERENGINE_H
#define GAMEOVERENGINE_H
#pragma once

#include "../DataGame/SFML/SfmlImage.hpp"

class GameOverEngine
{
public:
	GameOverEngine();
	~GameOverEngine();

	void draw(sf::RenderWindow &window);
	

	float transparence = 0;
	bool isGameOver = false;
	SfmlImage* gameOverImage;

private:

};
#endif
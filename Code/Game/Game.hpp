#ifndef GAME_H
#define GAME_H
#pragma once

#include "GameEngine.hpp"
#include "GameOverEngine.hpp"

#define WIDTH 1600
#define HEIGHT 1080

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	sf::RenderWindow *window;
	GameEngine *gameEngine;
	GameOverEngine *gameOverEngine;
	Camera *camera;

	sf::Clock timer;

	float deltaTime = 0;
	float dtLogic = 15;
	float updateTime = 0;

	void update();
};
#endif
#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <SFML/Graphics/View.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void update(sf::Vector2f playerPosition, float deltaTime);
	void input();
	sf::View &getView();

private:
	sf::View camera;

	float speedMove;

	sf::Vector2f getPourcentageOnScreen(sf::Vector2f object);
};
#endif
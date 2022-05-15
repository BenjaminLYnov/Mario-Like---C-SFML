#ifndef SFMLIMAGE_H
#define SFMLIMAGE_H
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class SfmlImage
{
public:
	SfmlImage();
	SfmlImage(std::string scr, int dimX, int dimY);
	SfmlImage(std::string scr, int dimX, int dimY, double posX, double posY);

	~SfmlImage();

	sf::Sprite &getSprite();
	void SetCentralOrigin();
	void SetFootOrigin();
	void draw(sf::RenderWindow &window) const;

private:
	sf::Texture texture;
	sf::Sprite sprite;
};
#endif
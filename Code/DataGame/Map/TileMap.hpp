#ifndef TILEMAP_H
#define TILEMAP_H
#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(const std::string &tileset, sf::Vector2u tileSize,  int *tiles, unsigned int width, unsigned int height);
	~TileMap();

private:
	bool load(const std::string &tileset, sf::Vector2u tileSize,  int *tiles, unsigned int width, unsigned int height);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};
#endif
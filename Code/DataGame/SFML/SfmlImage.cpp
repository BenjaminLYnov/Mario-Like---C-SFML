#include "SfmlImage.hpp"

SfmlImage::SfmlImage()
{
}

SfmlImage::SfmlImage(std::string scr, int dimX, int dimY)
{
     texture.loadFromFile(scr, sf::IntRect(0, 0, dimX, dimY));
     sprite.setTexture(texture);
}

SfmlImage::SfmlImage(std::string scr, int dimX, int dimY, double posX, double posY)
{
     texture.loadFromFile(scr, sf::IntRect(0, 0, dimX, dimY));
     sprite.setTexture(texture);
     sprite.setPosition(posX, posY);
}

SfmlImage::~SfmlImage()
{
}

sf::Sprite &SfmlImage::getSprite()
{
     return sprite;
}

void SfmlImage::draw(sf::RenderWindow &window) const
{
     window.draw(sprite);
}

void SfmlImage::SetCentralOrigin()
{
     sprite.setOrigin(fabs(sprite.getTextureRect().width / 2), fabs(sprite.getTextureRect().height / 2));
     // sprite.setOrigin(sprite.getTextureRect().width * fabs(sprite.getScale().x) / 2, sprite.getTextureRect().height * fabs(sprite.getScale().y) / 2);
}

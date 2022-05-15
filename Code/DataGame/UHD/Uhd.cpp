#include "Uhd.h"

Uhd::Uhd()
{
    font.loadFromFile("ressources/font/SuperMarioBros-ov7d.ttf");
    textCoin.setFont(font);
    coinImage = new SfmlImage("ressources/Images/pngkey.com-minecraft-block-png-2315228.png", 306, 353);
    coinImage->getSprite().setScale(0.05, 0.05);
}

Uhd::~Uhd()
{
    delete coinImage;
}

void Uhd::draw(sf::RenderWindow &window) const
{
    coinImage->draw(window);
    window.draw(textCoin);
}

void Uhd::update(sf::View camera)
{
    coinImage->getSprite().setPosition(camera.getCenter().x + camera.getSize().x / 3, camera.getCenter().y - camera.getSize().y / 3 - 80);
    textCoin.setPosition(camera.getCenter().x + camera.getSize().x / 3 + 20, camera.getCenter().y - camera.getSize().y / 3 - 90);
    textCoin.setString(std::to_string(nbrCoin));
}

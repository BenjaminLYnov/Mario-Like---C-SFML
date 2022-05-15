#ifndef UHD_H
#define UHD_H

#pragma once

#include "../SFML/SfmlImage.hpp"

class Uhd
{
public:
    Uhd();
    ~Uhd();

    void draw(sf::RenderWindow &window) const;
    void update(sf::View camera);

    int nbrCoin = 0;

private:
    SfmlImage *coinImage;

    sf::Font font;
    sf::Text textCoin;
};

#endif
#include "Coin.h"

Coin::Coin()
{
    sprite = new SfmlImage("ressources/Images/pngkey.com-minecraft-block-png-2315228.png", 306, 353);
}

Coin::Coin(float posX, float posY)
{
    sprite = new SfmlImage("ressources/Images/pngkey.com-minecraft-block-png-2315228.png", 306, 353, posX, posY);
    sprite->getSprite().setScale(0.05, 0.05);
    coinSound = new SfmlAudio("ressources/Sound/Snes Mario World/coin.wav");
}

Coin::~Coin()
{
    // delete coinSound;
}
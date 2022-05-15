#ifndef COIN_H
#define COIN_H

#pragma once
#include "../Actor/Actor.h"

class Coin : public Actor
{
public:
    Coin();
    Coin(float posX, float posY);
    ~Coin();

	SfmlAudio *coinSound;

private:

};

#endif
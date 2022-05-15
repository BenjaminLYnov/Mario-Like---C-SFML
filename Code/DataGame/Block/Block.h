#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include "../Actor/Actor.h"

class Block : public Actor
{
public:
    Block();
    Block(float posX, float posY);
    ~Block();

    bool hasChamp = true;
    void down();
	SfmlAudio *sproutItemSound;
private:

};

#endif
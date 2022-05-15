#include "Block.h"

Block::Block()
{
    sprite = new SfmlImage("ressources/Images/51a70c410a2f1cf.png", 1200, 1200, 500, 1000);
    sprite->getSprite().setScale(0.02, 0.02);
    sprite->SetCentralOrigin();
    sproutItemSound = new SfmlAudio("ressources/Sound/Snes Mario World/sprout-vine.wav");
}

Block::Block(float posX, float posY)
{
    sprite = new SfmlImage("ressources/Images/51a70c410a2f1cf.png", 1200, 1200, 500, 1000);
    sprite->getSprite().setScale(0.02, 0.02);
    sprite->SetCentralOrigin();
    sprite->getSprite().setPosition(posX, posY);
    sproutItemSound = new SfmlAudio("ressources/Sound/Snes Mario World/sprout-item.wav");

}

Block::~Block()
{
    // delete hitbox;
    // delete sproutItemSound;
}

void Block::down()
{
    hasChamp = false;
    sproutItemSound->sound.play();

    sprite = new SfmlImage("ressources/Images/y.png", 400, 400, sprite->getSprite().getPosition().x - 15, sprite->getSprite().getPosition().y - 15);
    sprite->getSprite().setScale(0.06, 0.06);
}

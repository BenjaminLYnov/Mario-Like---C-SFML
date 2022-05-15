#include "ParaGoomba.h"

ParaGoomba::ParaGoomba()
{
}

ParaGoomba::ParaGoomba(std::vector<sf::Vector2f> pos)
{
    init();
    sprite->getSprite().setPosition(pos[0]);

    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

ParaGoomba::ParaGoomba(float speedMove, std::vector<sf::Vector2f> pos)
{
    init();
    this->speedMove = speedMove;
    sprite->getSprite().setPosition(pos[0]);

    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

ParaGoomba::~ParaGoomba()
{
}

void ParaGoomba::performMovement(float deltaTime)
{
    if (hp > 0)
    {
        sf::Vector2f dir = wayPoint.getVectorDirectionPoint(sprite->getSprite().getPosition());
        sprite->getSprite().move(dir * speedMove * deltaTime);
        animationMove(deltaTime);
    }
    else
    {
        sprite->getSprite().move(0, -jumpSpeed * deltaTime);
        jumpSpeed -= 0.1;

        if (deathLeft)
            sprite->getSprite().move(-10, 0);
        else
            sprite->getSprite().move(10, 0);
    }
}

void ParaGoomba::init()
{
    initRect();
    sprite = new SfmlImage("ressources/Ennemie/Wii U - Paper Mario Color Splash - Goomba and Paragoomba.png", 1679, 2764);
    sprite->getSprite().setScale(0.2, 0.2);
    sprite->getSprite().setTextureRect(rec[0]);
    hp = 1;
}

void ParaGoomba::initRect()
{
    rec[0] = sf::IntRect(7, 2263, 154, 138);
    rec[1] = sf::IntRect(182, 2262, 184, 130);
    rec[2] = sf::IntRect(382, 2261, 157, 140);
    rec[3] = sf::IntRect(557, 2266, 182, 126);
    rec[4] = sf::IntRect(757, 2262, 154, 140);
}

void ParaGoomba::animationMove(float deltaTime)
{
    timerAnimation += deltaTime;
    
    if (timerAnimation > 100)
    {
        indexX++;
        indexX %= 5;
        timerAnimation = 0;
        sprite->getSprite().setTextureRect(rec[indexX]);
    }
}
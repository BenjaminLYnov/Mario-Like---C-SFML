#include "Rex.h"

Rex::Rex()
{
}

Rex::Rex(std::vector<sf::Vector2f> pos)
{
    init();
    sprite->getSprite().setPosition(pos[0]);
    sprite->getSprite().setTextureRect(rec[0][0]);
    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

Rex::Rex(float speedMove, std::vector<sf::Vector2f> pos)
{
    init();
    sprite->getSprite().setPosition(pos[0]);
    sprite->getSprite().setTextureRect(rec[0][0]);
    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
    this->speedMove = speedMove;
}

Rex::~Rex()
{
}

void Rex::init()
{
    initRect();
    sprite = new SfmlImage("ressources/Ennemie/SNES - Super Mario World - Rex Blargg & Dino-Rhino.png", 546, 230);
    hp = 2;
    sprite->getSprite().setScale(1.5, 1.5);
}

void Rex::performMovement(float deltaTime)
{
    if (hp > 0)
    {
        sf::Vector2f dir = wayPoint.getVectorDirectionPoint(sprite->getSprite().getPosition());

        // Change sprite side
        sf::Vector2f scale = sprite->getSprite().getScale();

        if (dir.x < 0)
        {
            if (scale.x < 0)
                scale.x = -scale.x;

            sprite->getSprite().setScale(scale.x, scale.y);

            if (wapaproundRight)
            {
                wapaproundRight = false;
                wapaproundLeft = true;
                sprite->getSprite().move(-sprite->getSprite().getTextureRect().width * scale.x, 0);
            }
        }
        else
        {
            if (scale.x > 0)
                scale.x = -scale.x;

            sprite->getSprite().setScale(scale.x, scale.y);

            if (wapaproundLeft)
            {
                wapaproundRight = true;
                wapaproundLeft = false;

                if (scale.x < 0)
                    scale.x = -scale.x;
                sprite->getSprite().move(sprite->getSprite().getTextureRect().width * scale.x, 0);
            }
        }

        sprite->getSprite().move(dir * speedMove * deltaTime);
        // std::cout << speedMove<< "\t" << dir.x  << "\n";
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

    gravity(deltaTime);
}

void Rex::animationMove(float deltaTime)
{
    timerAnimation += deltaTime;

    if (timerAnimation > 100)
    {
        indexY++;
        indexY %= 2;
        timerAnimation = 0;

        if (hp == 2)
            // Sprite grand
            sprite->getSprite().setTextureRect(rec[0][indexY]);
        else
            // Sprite small
            sprite->getSprite().setTextureRect(rec[1][indexY]);
    }
}

void Rex::initRect()
{
    rec[0][0] = sf::IntRect(8, 22, 22, 32);
    rec[0][1] = sf::IntRect(35, 22, 20, 32);

    rec[1][0] = sf::IntRect(86, 38, 18, 17);
    rec[1][1] = sf::IntRect(108, 38, 18, 16);
}
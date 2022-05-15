#include "Goomba.h"

Goomba::Goomba()
{
    init();
    wayPoint.addPoint(sf::Vector2f(0, 0));
}

Goomba::Goomba(std::vector<sf::Vector2f> pos)
{
    init();
    sprite->getSprite().setPosition(pos[0]);

    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

Goomba::Goomba(float speedMove, std::vector<sf::Vector2f> pos)
{
    init();
    hp = 1;
    this->speedMove = speedMove;
    sprite->getSprite().setPosition(pos[0]);

    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

Goomba::Goomba(float speedMove, float gravityForce, std::vector<sf::Vector2f> pos)
{
    init();
    hp = 1;
    this->speedMove = speedMove;
    this->gravityForce = gravityForce;
    sprite->getSprite().setPosition(pos[0]);

    for (int i = 0; i < pos.size(); i++)
        wayPoint.addPoint(pos[i]);
}

Goomba::~Goomba()
{
}

// Public Functions

void Goomba::performMovement(float deltaTime)
{
    if (hp > 0)
    {
        sf::Vector2f dir = wayPoint.getVectorDirectionPoint(sprite->getSprite().getPosition());

        // Change sprite side
        if (dir.x > 0)
            indexX = 0;
        else
            indexX = 1;

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

    gravity(deltaTime);
}

// Private Functions

void Goomba::animationMove(float deltaTime)
{
    timerAnimation += deltaTime;

    if (timerAnimation > 100)
    {
        indexY++;
        indexY %= 7;
        timerAnimation = 0;
        sprite->getSprite().setTextureRect(rec[indexX][indexY]);
    }
}

void Goomba::init()
{
    initRect();
    sprite = new SfmlImage("ressources/Ennemie/goomba_sheet-1.png", 236, 128);
    sprite->getSprite().setScale(1.5, 1.5);
    sprite->getSprite().setTextureRect(rec[0][0]);
    hp = 1;
}

void Goomba::initRect()
{
    rec[0][0] = sf::IntRect(7, 41, 19, 23);
    rec[0][1] = sf::IntRect(38, 41, 20, 23);
    rec[0][2] = sf::IntRect(70, 42, 20, 23);
    rec[0][3] = sf::IntRect(102, 42, 20, 23);
    rec[0][4] = sf::IntRect(134, 41, 20, 23);
    rec[0][5] = sf::IntRect(166, 42, 20, 23);
    rec[0][6] = sf::IntRect(198, 42, 19, 23);
    rec[0][7] = sf::IntRect(230, 41, 19, 23);

    rec[1][0] = sf::IntRect(6, 105, 20, 23);
    rec[1][1] = sf::IntRect(38, 105, 20, 23);
    rec[1][2] = sf::IntRect(70, 106, 20, 22);
    rec[1][3] = sf::IntRect(102, 106, 20, 22);
    rec[1][4] = sf::IntRect(134, 105, 20, 23);
    rec[1][5] = sf::IntRect(166, 105, 20, 23);
    rec[1][6] = sf::IntRect(198, 105, 20, 23);
    rec[1][7] = sf::IntRect(230, 106, 20, 23);
}

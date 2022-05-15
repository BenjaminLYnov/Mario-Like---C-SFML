#include "GameEngine.hpp"
#include <string>
#include <iostream>
#include "../DataGame/Math/RandomNumber.hpp"
#include "../DataGame/Math/Vector2D.hpp"
#include "../DataGame/Math/Radius.hpp"

// Template

template <typename T>
void checkGround(T &actor, Collider *collider)
{
    for (int j = 0; j < NBR_COLLIDER; j++)
    {
        actor.sprite->getSprite().move(0, 1);

        if (Collision::OnCollisionBySide("Up", actor.sprite->getSprite(), collider->getSprite(j)) ||
            Collision::OnCollisionBySide("Foot", actor.sprite->getSprite(), collider->getSprite(j)))
        {
            actor.isOnGround = true;
            actor.sprite->getSprite().move(0, -1);
            break;
        }
        else
        {
            actor.isOnGround = false;
        }
        actor.sprite->getSprite().move(0, -1);
    }
}

template <typename T>
void checkGround(std::vector<T> &actors, Collider *collider)
{
    for (int i = 0; i < actors.size(); i++)
    {
        for (int j = 0; j < NBR_COLLIDER; j++)
        {
            actors[i].sprite->getSprite().move(0, 1);

            if (Collision::OnCollisionBySide("Up", actors[i].sprite->getSprite(), collider->getSprite(j)) ||
                Collision::OnCollisionBySide("Foot", actors[i].sprite->getSprite(), collider->getSprite(j)))
            {
                actors[i].isOnGround = true;
                actors[i].sprite->getSprite().move(0, -1);
                break;
            }
            else
            {
                actors[i].isOnGround = false;
            }
            actors[i].sprite->getSprite().move(0, -1);
        }
    }
}

template <typename T>
void performMovement(std::vector<T> &actors, float deltaTime)
{
    for (int i = 0; i < actors.size(); i++)
        actors[i].performMovement(deltaTime);
}

template <typename T>
void cancelCollision(std::vector<T> &actors, Collider *collider)
{
    for (int i = 0; i < actors.size(); i++)
        if (actors[i].hp > 0)
            collider->notTrigger(actors[i].sprite->getSprite());
}

template <typename T>
void marioRebondOnEnnemie(Mario *mario, std::vector<T> &actors)
{
    for (int i = 0; i < actors.size(); i++)
    {

        if (actors[i].hp > 0)
        {
            if (mario->getVelocity().y > 0)
            {
                if (mario->footHitbox->getSprite().getPosition().y < actors[i].sprite->getSprite().getPosition().y + 20)
                {
                    if (Collision::PixelPerfectTest(mario->footHitbox->getSprite(), actors[i].sprite->getSprite()))
                    {
                        mario->jump.setJumpSpeed(0.7);
                        mario->state = JUMP;
                        mario->gravitySpeed = 0;
                        mario->getSprite().move(0, -mario->getSprite().getTextureRect().width * mario->getSprite().getScale().y);
                        mario->kickSound->sound.play();
                        actors[i].hp--;

                        if (RandomNumber::RandomInt(0, 1) == 0)
                            actors[i].deathLeft = false;
                    }
                }
            }
        }
    }
}

template <typename T>
void ennemieHurtMario(Mario *mario, std::vector<T> &actors)
{
    for (int i = 0; i < actors.size(); i++)
    {
        if (actors[i].hp > 0)
        {
            if (
                Collision::PixelPerfectTest(mario->leftHitbox->getSprite(), actors[i].sprite->getSprite()) ||
                Collision::PixelPerfectTest(mario->rightHitbox->getSprite(), actors[i].sprite->getSprite()) ||
                Collision::PixelPerfectTest(mario->headHitbox->getSprite(), actors[i].sprite->getSprite()))
            {
                mario->powerDown();
            }
        }
    }
}

template <typename T>
void drawActors(const std::vector<T> &actors, sf::RenderWindow &window)
{
    for (int i = 0; i < actors.size(); i++)
        actors[i].draw(window);
}

// End Template

GameEngine::GameEngine()
{
    map = new Map();
    mario = new Mario();
    collider = new Collider();
    uhd = new Uhd();

    flag = new SfmlImage("ressources/Images/142325.png", 56, 146, 11790, 1230);
    deadZone = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 1600);
    deadZone->getSprite().setScale(1000, 10);

    winMusic = new SfmlAudio("ressources/Sound/Super Mario World Music Level Complete.wav");
    mainTheme = new SfmlAudio("ressources/Music/overworld-theme-super-mario-world.wav");
    mainTheme->sound.play();
    mainTheme->sound.setLoop(true);

    initActor();
}

GameEngine::~GameEngine()
{
    delete map;
    delete mario;
    delete collider;
    delete uhd;
    delete flag;
    delete winMusic;
    delete deadZone;
    delete mainTheme;
}

// Public functions

void GameEngine::draw(sf::RenderWindow &window) const
{
    // Draw Game

    map->Draw(window);
    flag->draw(window);
    deadZone->draw(window);

    drawActors(goombas, window);
    drawActors(paraGoombas, window);
    drawActors(shrooms, window);
    drawActors(rexs, window);

    drawActors(blocks, window);
    drawActors(coins, window);

    mario->draw(window);
    uhd->draw(window);
}

void GameEngine::run(float deltaTime)
{
    if (mario->isTransforming)
    {
        mario->transforming(deltaTime);
    }
    else
    {
        if (!isWon)
        {
            // Update Game Logic
            update(deltaTime);

            // Move Actors
            performActorsMovement(deltaTime);

            // Collision step
            collisionStep();
        }

        winEngine(deltaTime);
    }
}

sf::Vector2f GameEngine::getMarioPosition()
{
    return mario->getSprite().getPosition();
}

// Private Functions

// Initiation

void GameEngine::initActor()
{
    rexs.push_back(Rex({sf::Vector2f(1400, 1350), sf::Vector2f(1750, 1350)}));
    rexs.push_back(Rex({sf::Vector2f(1865, 1310), sf::Vector2f(1950, 1310)}));
    rexs.push_back(Rex({sf::Vector2f(1980, 1350), sf::Vector2f(2140, 1350)}));
    rexs.push_back(Rex(0.2, {sf::Vector2f(3500, 1340), sf::Vector2f(3700, 1340)}));
    rexs.push_back(Rex(0.5, {sf::Vector2f(6444, 1340), sf::Vector2f(6730, 1340)}));
    rexs.push_back(Rex(0.6, {sf::Vector2f(6550, 1340), sf::Vector2f(6680, 1340)}));
    rexs.push_back(Rex(0.6, {sf::Vector2f(8000, 1340), sf::Vector2f(8300, 1340)}));
    rexs.push_back(Rex(0.6, {sf::Vector2f(8400, 1340), sf::Vector2f(8600, 1340)}));
    rexs.push_back(Rex(2, {sf::Vector2f(8400, 1340), sf::Vector2f(9495, 1340)}));
    rexs.push_back(Rex(0.2, {sf::Vector2f(8585, 1200), sf::Vector2f(8822, 1200)}));
    rexs.push_back(Rex(0.2, {sf::Vector2f(8900, 1200), sf::Vector2f(9200, 1200)}));
    rexs.push_back(Rex(0.2, {sf::Vector2f(8640, 1060), sf::Vector2f(8960, 1060)}));
    rexs.push_back(Rex(0.2, {sf::Vector2f(9090, 1060), sf::Vector2f(8686, 1060)}));

    goombas.push_back(Goomba({sf::Vector2f(520, 1350), sf::Vector2f(720, 1350)}));
    goombas.push_back(Goomba({sf::Vector2f(740, 1350), sf::Vector2f(1000, 1350)}));
    goombas.push_back(Goomba({sf::Vector2f(1140, 1350)}));
    goombas.push_back(Goomba({sf::Vector2f(1270, 1350)}));
    goombas.push_back(Goomba(0.5, {sf::Vector2f(2300, 1350), sf::Vector2f(3000, 1350)}));
    goombas.push_back(Goomba(0.3, {sf::Vector2f(3360, 1340), sf::Vector2f(3800, 1340)}));
    goombas.push_back(Goomba(0.3, {sf::Vector2f(7375, 1340), sf::Vector2f(7677, 1340)}));
    goombas.push_back(Goomba(0.3, {sf::Vector2f(7275, 1340), sf::Vector2f(7577, 1340)}));
    goombas.push_back(Goomba(0.3, {sf::Vector2f(7648, 1340), sf::Vector2f(7877, 1340)}));
    goombas.push_back(Goomba(0.3, {sf::Vector2f(7500, 1340), sf::Vector2f(8100, 1340)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(3900, 1327)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(4050, 1327)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(4200, 1327)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(4919, 1200), sf::Vector2f(4919, 1450)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(5175, 1200), sf::Vector2f(5175, 1450)}));
    goombas.push_back(Goomba(0.4, 0, {sf::Vector2f(5595, 1100), sf::Vector2f(5595, 1450)}));
    goombas.push_back(Goomba(0.4, 0, {sf::Vector2f(5810, 1100), sf::Vector2f(5810, 1450)}));
    goombas.push_back(Goomba(0.7, 0, {sf::Vector2f(6020, 1000), sf::Vector2f(6020, 1500)}));
    goombas.push_back(Goomba(1, 0, {sf::Vector2f(6790, 1100), sf::Vector2f(6890, 1200), sf::Vector2f(6800, 1500), sf::Vector2f(6787, 1340), sf::Vector2f(6894, 1400)}));
    goombas.push_back(Goomba(1, 0, {sf::Vector2f(7486, 1080), sf::Vector2f(7694, 1300), sf::Vector2f(7885, 950), sf::Vector2f(7600, 930), sf::Vector2f(7400, 940)}));
    goombas.push_back(Goomba(1, 0, {sf::Vector2f(7995, 990), sf::Vector2f(7995, 1200), sf::Vector2f(7935, 990), sf::Vector2f(7935, 1200)}));
    goombas.push_back(Goomba(2, 0, {sf::Vector2f(8218, 1300), sf::Vector2f(8447, 1171), sf::Vector2f(8221, 1146)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(9800, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(9900, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10000, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10100, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10200, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10300, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10400, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10500, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10600, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10700, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10800, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(10900, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11000, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11100, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11200, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11300, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11400, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11500, 1376)}));
    goombas.push_back(Goomba(0.1, 0, {sf::Vector2f(11600, 1376)}));

    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(0, 1327)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(3900, 1327)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(4050, 1327)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(4200, 1327)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(4919, 1200), sf::Vector2f(4919, 1450)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(5175, 1200), sf::Vector2f(5175, 1450)}));
    // paraGoombas.push_back(ParaGoomba(0.4, {sf::Vector2f(5595, 1100), sf::Vector2f(5595, 1450)}));
    // paraGoombas.push_back(ParaGoomba(0.4, {sf::Vector2f(5810, 1100), sf::Vector2f(5810, 1450)}));
    // paraGoombas.push_back(ParaGoomba(0.7, {sf::Vector2f(6020, 1000), sf::Vector2f(6020, 1500)}));
    // paraGoombas.push_back(ParaGoomba(1, {sf::Vector2f(6790, 1100), sf::Vector2f(6890, 1200), sf::Vector2f(6800, 1500), sf::Vector2f(6787, 1340), sf::Vector2f(6894, 1400)}));

    // paraGoombas.push_back(ParaGoomba(1, {sf::Vector2f(7486, 1080), sf::Vector2f(7694, 1300), sf::Vector2f(7885, 950), sf::Vector2f(7600, 930), sf::Vector2f(7400, 940)}));
    // paraGoombas.push_back(ParaGoomba(1, {sf::Vector2f(7995, 990), sf::Vector2f(7995, 1200), sf::Vector2f(7935, 990), sf::Vector2f(7935, 1200)}));
    // paraGoombas.push_back(ParaGoomba(2, {sf::Vector2f(8218, 1300), sf::Vector2f(8447, 1171), sf::Vector2f(8221, 1146)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(9800, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(9900, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10000, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10100, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10200, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10300, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10400, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10500, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10600, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10700, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10800, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(10900, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11000, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11100, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11200, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11300, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11400, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11500, 1376)}));
    // paraGoombas.push_back(ParaGoomba({sf::Vector2f(11600, 1376)}));

    blocks.push_back(Block(120, 1262));
    blocks.push_back(Block(1450, 1230));
    blocks.push_back(Block(3300, 1200));
    blocks.push_back(Block(6400, 1260));
    blocks.push_back(Block(4400, 1200));
    blocks.push_back(Block(7150, 1100));

    coins.push_back(Coin(390, 1157));
    coins.push_back(Coin(626, 1337));
    coins.push_back(Coin(884, 1337));
    coins.push_back(Coin(1155, 1250));
    coins.push_back(Coin(1278, 1250));
    coins.push_back(Coin(1543, 1124));
    coins.push_back(Coin(2500, 1226));
    coins.push_back(Coin(2800, 1262));
    coins.push_back(Coin(3400, 1070));
    coins.push_back(Coin(3978, 1200));
    coins.push_back(Coin(3978, 1200));
    coins.push_back(Coin(4142, 1200));
    coins.push_back(Coin(4931, 1100));
    coins.push_back(Coin(5190, 1100));
    coins.push_back(Coin(5699, 1100));
    coins.push_back(Coin(5916, 960));
    coins.push_back(Coin(7700, 1300));
    coins.push_back(Coin(7689, 1048));
    coins.push_back(Coin(8118, 1191));
    coins.push_back(Coin(9000, 1300));

    for (int i = 0; i < 19; i++)
    {
        coins.push_back(Coin(9860 + i * 100, 1250));
    }
}

// Update Game Logic
void GameEngine::update(float deltaTime)
{
    mario->update(deltaTime);
    shroomMarioPowerUp();
}

// Move actors
void GameEngine::performActorsMovement(float deltaTime)
{
    mario->performMovement(deltaTime);

    // Limite mario pos X < 0
    if (mario->getSprite().getPosition().x < 0)
        mario->getSprite().setPosition(0, mario->getSprite().getPosition().y);

    performMovement(rexs, deltaTime);
    performMovement(goombas, deltaTime);
    performMovement(paraGoombas, deltaTime);
    performMovement(shrooms, deltaTime);
}

// Collision Step
void GameEngine::collisionStep()
{
    // Check if actors is on ground, if true =>reset gravity speed to 0
    checkActorOnGround();

    marioHeadOnBlock();

    marioGetHurt();

    // Jump on goombas
    marioRebondOnEnnemies();

    marioCollisionOnCoin();

    // Make game over if mario is on dead zone
    instantKillMario();

    changeShroomDirection();

    // Cancel collision
    collisionNotTrigger();
}

// Cancel gravity if actor is on ground
void GameEngine::checkActorOnGround()
{
    checkMarioJump();
    checkGround(shrooms, collider);
    checkGround(goombas, collider);
    checkGround(rexs, collider);

    for (int i = 0; i < shrooms.size(); i++)
    {
        for (int j = 0; j < blocks.size(); j++)
        {
            shrooms[i].sprite->getSprite().move(0, 1);

            if (Collision::OnCollisionBySide("Up", shrooms[i].sprite->getSprite(), blocks[j].sprite->getSprite()) ||
                Collision::OnCollisionBySide("Foot", shrooms[i].sprite->getSprite(), blocks[j].sprite->getSprite()))
            {
                shrooms[i].isOnGround = true;
                shrooms[i].sprite->getSprite().move(0, -1);
                break;
            }
            shrooms[i].sprite->getSprite().move(0, -1);
        }
    }
}

void GameEngine::checkMarioJump()
{
    for (int i = 0; i < NBR_COLLIDER; i++)
    {
        mario->setCanJump(false);

        mario->footHitbox->getSprite().move(0, 1);

        if (Collision::PixelPerfectTest(mario->footHitbox->getSprite(), collider->getSprite(i)))
        {
            mario->setCanJump(true);
            mario->footHitbox->getSprite().move(0, -1);
            mario->gravitySpeed = 0;
            return;
        }
        mario->footHitbox->getSprite().move(0, -1);
    }

    for (int i = 0; i < blocks.size(); i++)
    {
        mario->setCanJump(false);

        mario->footHitbox->getSprite().move(0, 1);

        if (Collision::PixelPerfectTest(mario->footHitbox->getSprite(), blocks[i].sprite->getSprite()))
        {
            mario->setCanJump(true);
            mario->footHitbox->getSprite().move(0, -1);
            mario->gravitySpeed = 0;
            return;
        }
        mario->footHitbox->getSprite().move(0, -1);
    }
}

// Cancel collision
void GameEngine::collisionNotTrigger()
{
    for (int i = 0; i < NBR_COLLIDER; i++)
        cancelMarioCollision(collider->getSprite(i));

    for (int i = 0; i < blocks.size(); i++)
        cancelMarioCollision(blocks[i].sprite->getSprite());

    cancelCollision(rexs, collider);
    cancelCollision(shrooms, collider);
    cancelCollision(goombas, collider);
    cancelCollision(paraGoombas, collider);
}

void GameEngine::cancelMarioCollision(sf::Sprite &box)
{
    while (Collision::PixelPerfectTest(mario->headHitbox->getSprite(), box))
    {
        mario->getSprite().move(0, 1);
        mario->setPositionHitbox();
    }

    while (Collision::PixelPerfectTest(mario->rightHitbox->getSprite(), box))
    {
        mario->getSprite().move(-1, 0);
        mario->setPositionHitbox();
    }

    while (Collision::PixelPerfectTest(mario->leftHitbox->getSprite(), box))
    {
        mario->getSprite().move(1, 0);
        mario->setPositionHitbox();
    }

    while (Collision::PixelPerfectTest(mario->footHitbox->getSprite(), box))
    {
        mario->getSprite().move(0, -1);
        mario->setPositionHitbox();
    }
}

// Mario jump on ennemie
void GameEngine::marioRebondOnEnnemies()
{
    marioRebondOnEnnemie(mario, goombas);
    marioRebondOnEnnemie(mario, paraGoombas);
    marioRebondOnEnnemie(mario, rexs);
}

// Power down mario on collision with ennemie
void GameEngine::marioGetHurt()
{
    if (mario->currentInvulnerableTime == 0)
    {
        ennemieHurtMario(mario, rexs);
        ennemieHurtMario(mario, goombas);
        ennemieHurtMario(mario, paraGoombas);

        // Stop Music if mario is dead
        if (!mario->isAlive)
        {
            mainTheme->sound.stop();
        }
    }
}

void GameEngine::instantKillMario()
{
    if (Collision::PixelPerfectTest(mario->getSprite(), deadZone->getSprite()))
    {
        mario->makeDead();
        mainTheme->sound.stop();
    }
}

void GameEngine::marioCollisionOnCoin()
{
    for (int i = 0; i < coins.size(); i++)
        if (Collision::PixelPerfectTest(mario->getSprite(), coins[i].sprite->getSprite()))
        {
            coins.erase(coins.begin() + i);
            coins[i].coinSound->sound.play();
            uhd->nbrCoin++;
        }
}

void GameEngine::marioHeadOnBlock()
{
    if (mario->getVelocity().y < 0)
    {

        for (int i = 0; i < NBR_COLLIDER; i++)
        {
            if (Collision::PixelPerfectTest(mario->headHitbox->getSprite(), collider->getSprite(i)))
            {
                mario->jump.setJumpSpeed(0);
                mario->getSprite().move(0, 1);
                mario->setPositionHitbox();
                break;
            }
        }

        for (int i = 0; i < blocks.size(); i++)
        {
            while (Collision::PixelPerfectTest(mario->footHitbox->getSprite(), blocks[i].sprite->getSprite()))
            {
                mario->getSprite().move(0, -1);
                mario->setPositionHitbox();
            }

            bool headIsOnBlock = false;

            while (Collision::PixelPerfectTest(mario->headHitbox->getSprite(), blocks[i].sprite->getSprite()))
            {
                mario->getSprite().move(0, 1);
                mario->setPositionHitbox();
                mario->jump.jumpSpeed = 0;
                mario->jump.setJumpSpeed(0);
                headIsOnBlock = true;
            }

            if (headIsOnBlock && blocks[i].hasChamp)
            {
                blocks[i].down();
                shrooms.push_back(Shroom(blocks[i].sprite->getSprite().getPosition().x, blocks[i].sprite->getSprite().getPosition().y - fabs(blocks[i].sprite->getSprite().getTextureRect().height * fabs(blocks[i].sprite->getSprite().getScale().y)) - 5));
            }
        }
    }
}

void GameEngine::shroomMarioPowerUp()
{
    for (int i = 0; i < shrooms.size(); i++)
        if (Collision::PixelPerfectTest(mario->getSprite(), shrooms[i].sprite->getSprite()))
        {
            shrooms.erase(shrooms.begin() + i);
            mario->powerUp();
        }
}

void GameEngine::changeShroomDirection()
{
    for (int i = 0; i < shrooms.size(); i++)
        for (int j = 0; j < NBR_COLLIDER; j++)
        {
            if (Collision::OnCollisionBySide("Left", shrooms[i].sprite->getSprite(), collider->getSprite(j)) ||
                Collision::OnCollisionBySide("Right", shrooms[i].sprite->getSprite(), collider->getSprite(j)))
            {
                shrooms[i].changeDirection();
                break;
            }
        }
}

// Win gear functions

void GameEngine::winEngine(float deltaTime)
{
    winCondition();

    if (isWon)
    {
        playMusicWin();

        winTimer += deltaTime;

        if (winTimer < 7000)
        {
            makeMarioMoveRight(deltaTime);
        }
        else
            mario->setIdle();

        if (winTimer > 7300)
        {
            mario->setMarioVictoryStyle();
        }

        // Down mario (gravity)
        float yMov = 0;
        yMov = mario->gravitySpeed * deltaTime;
        mario->getSprite().move(0, yMov);

        // Cancel collision mario on ground
        while (Collision::PixelPerfectTest(mario->getSprite(), collider->getSprite(NBR_COLLIDER - 1)))
        {
            mario->setCanJump(true);
            mario->getSprite().move(0, -1);
            mario->gravitySpeed = 0;
        }
    }
}

void GameEngine::winCondition()
{
    if (Collision::PixelPerfectTest(mario->getSprite(), flag->getSprite()))
        isWon = true;
}

void GameEngine::makeMarioMoveRight(float deltaTime)
{
    mario->getSprite().setScale(-fabs(mario->getSprite().getScale().x), mario->getSprite().getScale().y);
    if (mario->gravitySpeed == 0)
        mario->animationWalk(deltaTime);

    float xMov = 0;

    xMov = mario->speedMove * deltaTime;

    mario->getSprite().move(xMov, 0);
    mario->setPositionHitbox();
}

void GameEngine::playMusicWin()
{
    if (playWinMusicOnce)
    {
        playWinMusicOnce = false;
        winMusic->sound.play();
        mainTheme->sound.stop();
    }
}

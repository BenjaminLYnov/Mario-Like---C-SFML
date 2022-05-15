#include "GameOverEngine.hpp"

GameOverEngine::GameOverEngine()
{
    gameOverImage = new SfmlImage("ressources/Images/gameOver.png", 1270, 659);
    gameOverImage->SetCentralOrigin();
}

GameOverEngine::~GameOverEngine()
{
    delete gameOverImage;
}

void GameOverEngine::draw(sf::RenderWindow &window)
{
    gameOverImage->draw(window);
}

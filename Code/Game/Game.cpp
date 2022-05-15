#include "Game.hpp"
#include "iostream"

Game::Game()
{
    srand(time(NULL)); // To get new alea number at each lauching

    gameEngine = new GameEngine();
    gameOverEngine = new GameOverEngine();

    camera = new Camera();

    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Mario Like");
    window->setFramerateLimit(60); // Block game at 60 FPS
}

Game::~Game()
{
    delete window;
    delete gameEngine;
    delete gameOverEngine;
    delete camera;
}

void Game::run()
{
    sf::Event event;

    // Window's Game
    while (window->isOpen())
    {
        // Delta Time
        deltaTime = timer.getElapsedTime().asMilliseconds();
        updateTime += deltaTime;
        timer.restart();

        // Check Event
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Update logic game at fixed timesteps
        while (updateTime >= dtLogic)
        {
            if (gameEngine->mario->isAlive)
            {
                gameEngine->run(dtLogic);

                // Update camera position
                camera->update(gameEngine->getMarioPosition(), dtLogic);
                gameEngine->uhd->update(camera->getView());

                // Background Parallax
                gameEngine->map->moveBackgroundParallax(camera->getView().getCenter());
            }
            else
            {
                gameEngine->mario->deathing(deltaTime);
                if (gameEngine->mario->currendDeathingTime > 3200)
                {
                    gameOverEngine->isGameOver = true;
                }
            }
            updateTime -= dtLogic;
        }

        // Refresh window view
        window->setView(camera->getView());

        if (!gameOverEngine->isGameOver)
        {
            // Show game on the window
            window->clear(sf::Color(0, 134, 255));
            gameEngine->draw(*window);
        }
        else
        {
            // Show Game Over Image by increase his transparence
            window->clear(sf::Color(0, 0, 0));
            gameOverEngine->gameOverImage->getSprite().setColor(sf::Color(255, 255, 255, gameOverEngine->transparence));
            gameOverEngine->gameOverImage->getSprite().setPosition(camera->getView().getCenter());
            gameOverEngine->draw(*window);

            if (gameOverEngine->transparence < 255)
                gameOverEngine->transparence += 1;
        }

        window->display();

        if (gameEngine->mario->currendDeathingTime > 15000 || gameEngine->winTimer > 15000)
            window->close();
    }
}

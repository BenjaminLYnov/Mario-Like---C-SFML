#include "Camera.hpp"
#include "../Math/Vector2D.hpp"
#include "../../System/Input.h"

Camera::Camera()
{
    camera = sf::View(sf::FloatRect(800, 540, -400, 1000));
    camera.setSize(800, 500);
    camera.setCenter(410, 1190);
    speedMove = 20;
}

Camera::~Camera()
{
}

void Camera::update(sf::Vector2f playerPosition, float deltaTime)
{
    deltaTime /= 100;

    sf::Vector2f pourcentage = getPourcentageOnScreen(playerPosition);
    float distance = Vector2D::Distance(camera.getCenter(), playerPosition) / 100;
    if (pourcentage.x >= 60)
        camera.move(speedMove * deltaTime * distance, 0);
    else if (pourcentage.x <= 40 && camera.getCenter().x >= 410)
        camera.move(-speedMove * deltaTime * distance, 0);

    // float xMov = Input::getAxisRaw("Horizontal") * deltaTime;
    // float yMov = Input::getAxisRaw("Vertical") * deltaTime;
    // camera.move(xMov, yMov);

    // std::cout << camera.getCenter().x << "\t" << camera.getCenter().y << "\n";
}

sf::Vector2f Camera::getPourcentageOnScreen(sf::Vector2f object)
{
    sf::Vector2f pourcentage;
    pourcentage.x = (object.x - camera.getCenter().x + camera.getSize().x / 2) * 100 / camera.getSize().x;
    pourcentage.y = (object.y - camera.getCenter().y + camera.getSize().y / 2) * 100 / camera.getSize().y;
    return pourcentage;
}

sf::View &Camera::getView()
{
    return camera;
}
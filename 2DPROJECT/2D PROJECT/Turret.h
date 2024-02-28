#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Tank.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <Thor/Resources.hpp>
#include<LevelLoader.h>
#include "CollisionDetector.h"
#include"Bullet.cpp"
#pragma once

#include <SFML/Graphics.hpp>

class Turret {
public:
    Turret();

    void update(float dt, sf::Vector2f& targetPosition, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void setFireFreq(double amount);
    sf::Vector2f getPosition();
    void setPos(double x, double y);
    void followPlayer(double rotation);
    void fire(float dt);
    Bullet bullets[100];

private:
    int bulletCounter = 0;
    sf::Vector2f position;
    float rotationSpeed;
    double firingFrequency;
    sf::Clock firingTimer;
    sf::Texture turretTexture;
    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;
    sf::Sprite turretSprite;
    float new_rotation;
    // Add other turret properties

    // You may want to have a Projectile class or struct to represent the turret's projectiles
    // Example: std::vector<Projectile> projectiles;
};


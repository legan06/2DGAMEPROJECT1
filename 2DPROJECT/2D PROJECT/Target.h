#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "ScreenSize.h"
#include <Thor/Resources.hpp>
#include<LevelLoader.h>
#include "CollisionDetector.h"

class StaticTarget {
public:
    StaticTarget(float x, float y, float duration, float initialSize)
        : position(x, y), duration(duration), size(initialSize) {}

    void update(float dt) {
        duration -= dt;
        size *= (duration > 0) ? 0.99 : 1.0;  // Shrink over time
    }

    void draw(sf::RenderWindow& window) const {
        // Implement drawing logic based on the position, size, etc.
        // Example: sf::RectangleShape with position and size
    }
    void initSprites();
    void render();

private:
    sf::Vector2f position;
    float duration;
    float size;
    sf::Sprite m_staticTarget;
};

class TurretTarget {
public:
    TurretTarget(float x, float y, float rotationSpeed, float firingFrequency)
        : position(x, y), rotationSpeed(rotationSpeed), firingFrequency(firingFrequency) {
        // Initialize other properties
    }

    void update(float dt) {
        // Update turret properties, e.g., rotation, firing logic, etc.
    }

    void draw(sf::RenderWindow& window) const {
    }

private:
    sf::Vector2f position;
    float rotationSpeed;
    float firingFrequency;
    sf::Sprite turretTarget;
};

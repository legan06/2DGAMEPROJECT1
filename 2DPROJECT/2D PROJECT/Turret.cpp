#include "Turret.h"
#define M_PI 3.14159265358979323846
#include"Bullet.cpp"


Turret::Turret()
    : position(0.0f, 0.0f), rotationSpeed(0.0f), firingFrequency(0.0f) {

    if (!turretTexture.loadFromFile("resources/images/turret.png")) {
    }

    turretSprite.setTexture(turretTexture);
    turretSprite.setScale(0.2f, 0.2f);
    turretSprite.setOrigin(turretSprite.getLocalBounds().width/2,turretSprite.getLocalBounds().height / 2);

}



void Turret::setFireFreq(double value) {
    firingFrequency=value;
    
}


void Turret::fire(float dt) {
    if (bulletCounter < 10) {
        Bullet bullet(turretSprite.getPosition().x+50, turretSprite.getPosition().y+50, new_rotation, dt);
        bullets[bulletCounter] = bullet;
    }

}


void Turret::update(float dt, sf::Vector2f& targetPosition, sf::RenderWindow& window) {
    printf("%d", bulletCounter);
    for (int i = 0; i < bulletCounter; i++) {
        bullets[i].move();
        bullets[i].draw(window);
    }



    // Calculate the direction vector from turret to target position
    sf::Vector2f direction = targetPosition - turretSprite.getPosition();

    // Calculate the rotation angle
    new_rotation = std::atan2(direction.y, direction.x) * (180.0f / static_cast<float>(M_PI));

    // Set the turret's rotation
    turretSprite.setRotation(new_rotation+180);
    // Firing logic
    if (firingTimer.getElapsedTime().asSeconds() > firingFrequency) {
        // Fire projectile or perform firing logic
        fire(dt);
        bulletCounter++;

        firingTimer.restart();  // Reset the firing timer
    }


}

void Turret::draw(sf::RenderWindow& window) const {

    window.draw(turretSprite);


}

void  Turret::setPos(double x, double y) {
    turretSprite.setPosition(x, y);
}
sf::Vector2f Turret::getPosition() {
    return turretSprite.getPosition();
}


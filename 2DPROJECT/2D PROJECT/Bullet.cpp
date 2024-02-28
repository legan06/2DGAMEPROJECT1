#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Tank.h"
#include <string>
#include<LevelLoader.h>
#include "CollisionDetector.h"
#include"MathUtility.h"
class Bullet {
private:
	double rotation;
	sf::Vector2f position;
	double speed=1000;
	double dt;
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	float radians;
public:

	Bullet() {

	}
	
	Bullet(double posX, double posY,double _rotation,double _dt) {
		if (!bulletTexture.loadFromFile("resources/images/spritesheet.png")) {
		}
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setTextureRect(sf::IntRect(247, 95, 128, 128));
		bulletSprite.setPosition(posX, posY);
		rotation = _rotation;
		dt = _dt;
		radians = thor::toRadian(rotation);
	}

	void move() {
		sf::Vector2f velocity(std::cos(radians) * speed * (dt / 1000.0),
			std::sin(radians) * speed * (dt / 1000.0));
		bulletSprite.setPosition(bulletSprite.getPosition() + sf::Vector2f(0,3));

	}

	void draw(sf::RenderWindow& window) {

		window.draw(bulletSprite);

	}

};
#include "Tank.h"
#include"MathUtility.h"
#include <Thor/Resources.hpp>
Tank::Tank(thor::ResourceHolder<sf::Texture, std::string>& t_holder,

	std::vector<sf::Sprite>& t_wallSprites)

	: m_holder(t_holder),

	m_wallSprites(t_wallSprites)

{
	initSprites();

}



double DEG_TO_RAD = std::numbers::pi / 180.0f;
void Tank::update(double dt)
{
	m_dt = dt;
	CollisionDetector coll;

	for (sf::Sprite const& sprite : m_wallSprites) {
		if (coll.collision(m_tankBase, sprite)) {
			m_contactNormal = m_tankBase.getPosition() - sprite.getPosition();
			deflect();

		}
		else if (coll.collision(m_turret, sprite)) {
			m_contactNormal = m_turret.getPosition() - sprite.getPosition();
			deflect();
		}
		else if (coll.collision(m_bulletSprite, sprite)) {
			m_contactNormal = m_bulletSprite.getPosition() - sprite.getPosition();

			// Reset bullet position to (2000, 2000) on collision with wall
			m_bulletSprite.setPosition(2000, 2000);
			bulletSpeed = 0;
			deflect();
		}

	}


	if (reloading == true) {
		secondCounter--;
		if (secondCounter == 0) {
			secondCounter = 60;
			reloading = false;
		}
	}

		if (m_shouldRotateTurret)
		{
			centreTurret();

		}

		// Limit the turret rotation to a specific range (adjust as needed)
		m_turretRotation = (m_turretRotation > MAX_TURRET_ROTATION) ? MAX_TURRET_ROTATION :
			(m_turretRotation < MIN_TURRET_ROTATION) ? MIN_TURRET_ROTATION : m_turretRotation;
		// Set the rotation of the turret sprite
		float radians_turret= thor::toRadian(m_turretRotation);
		 

		handleKeyInput();
		m_speed *= 0.99;
		m_speed = (m_speed > MAX_FORWARD_SPEED) ? MAX_FORWARD_SPEED :
			(m_speed < MAX_REVERSE_SPEED) ? MAX_REVERSE_SPEED : m_speed;
		float radians = thor::toRadian(m_rotation); // Convert rotation to radians
		sf::Vector2f velocity(std::cos(radians) * m_speed * (dt / 1000.0),
			std::sin(radians) * m_speed * (dt / 1000.0));

		// Calculate the new position
		sf::Vector2f newPosition = m_tankBase.getPosition() + velocity;
		
		//bullet movement
        sf::Vector2f velocity_bullet(std::cos(bulletRotation) * bulletSpeed * (dt / 1000.0),
            std::sin(bulletRotation) * bulletSpeed * (dt / 1000.0));
        sf::Vector2f bulletPosition = m_bulletSprite.getPosition() + velocity_bullet;
		m_bulletSprite.setPosition(bulletPosition);
		// Move the tank base to the new position
		m_tankBase.setPosition(newPosition);
		m_turret.setPosition(newPosition- sf::Vector2f(0,0));

}

void Tank::render(sf::RenderWindow & window) 
{

	m_tankBase.setRotation(static_cast<float>(m_rotation));
	m_turret.setRotation(static_cast<float>(m_rotation+m_turretRotation));

	window.draw(m_bulletSprite);

	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::setPosition(sf::Vector2f t_position)
{
	m_tankBase.setPosition(t_position);
	m_turret.setPosition(t_position);
}

sf::Vector2f Tank::getPosition()
{
	return m_tankBase.getPosition();
}
void Tank::increaseTurretRotation()
{
	m_turretRotation += 1;
}

void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 1;
}


void Tank::setScale(sf::Vector2f t_scale)
{
	m_tankBase.setScale(t_scale);
	m_turret.setScale(t_scale);
}
void Tank::increaseSpeed() { m_speed += 1; }  
void Tank::decreaseSpeed() { 
	m_speed -= 1;
}
void Tank::increaseRotation() { 
	

	m_rotation += 1; 
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Tank::deflect()
{

	// Calculate impulse based on speed

	float impulseMagnitude = std::abs(m_speed);

	// Normalise the contact vector

	m_contactNormal = thor::unitVector(m_contactNormal);

	// Calculate deflection amount
	
	deflectVector =

	{

	impulseMagnitude * m_contactNormal.x * (static_cast<float>(m_dt) / 1000),

	impulseMagnitude * m_contactNormal.y * (static_cast<float>(m_dt) / 1000)

	};

	// Apply impulse along the contact normal

	m_tankBase.move(deflectVector.x, deflectVector.y);

	m_turret.move(deflectVector.x, deflectVector.y);

}
void Tank::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation < 0.0)
	{
		m_rotation = 359.0;
	}
}

void Tank::fire() {
	// Create a new bullet sprite

	// Set the position and rotation for the bullet
	bulletSpeed = 1000;
	m_bulletSprite.setPosition(m_tankBase.getPosition()+sf::Vector2f(50,-50));
	m_bulletSprite.setRotation(m_turret.getRotation()+90);

	// Add the bullet to the vector


	printf("Fired\n");

}
void Tank::handleKeyInput() {
	// Handle key input for tank movement using sf::Keyboard::isKeyPressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		decreaseTurretRotation();
	}
	//Rotating back the turret
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		m_shouldRotateTurret = true;
		m_initialTurretRotation = m_turretRotation;
		m_destTurretRotation = 0.0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

		if (reloading == false) {
			bulletRotation = thor::toRadian(m_turret.getRotation() );
			fire();
			reloading = true;
		}
	}
}
void Tank::centreTurret()
{
	const double degreesPerFrame = 1.0;

	// Calculate the shortest direction to rotate
	if (m_initialTurretRotation >= 180.0)
		m_destTurretRotation += 360.0;
	else if (m_destTurretRotation >= 180.0)
		m_initialTurretRotation += 360.0;

	if (m_initialTurretRotation < m_destTurretRotation)
		m_rotationDirection = 1;
	else
		m_rotationDirection = -1;


	m_turretRotation += m_rotationDirection * degreesPerFrame;


	if ((m_rotationDirection == 1 && m_turretRotation >= m_destTurretRotation) ||
		(m_rotationDirection == -1 && m_turretRotation <= m_destTurretRotation))
	{
		m_shouldRotateTurret = false; 
	}
}

void Tank::initSprites()
{

	m_holder.acquire("bgSprite", thor::Resources::fromFile<sf::Texture>("resources/images/Background.jpg"));
	m_holder.acquire("tankAtlas", thor::Resources::fromFile<sf::Texture>("resources/images/spritesheet.png"));

	sf::Texture& texture = m_holder["tankAtlas"];


	m_bulletSprite.setTextureRect(sf::IntRect(247, 95, 128, 128));
	m_bulletSprite.setTexture(texture);
	m_bulletSprite.setPosition(2000,2000);

	m_turret.setTexture(texture);
	m_turret.setTextureRect(sf::IntRect(247, 0, 191, 94));
	m_turret.setOrigin(30, 50);
	//m_turret.setOrigin(m_turret.getLocalBounds().width / 2-40, m_turret.getLocalBounds().height / 2);
	m_tankBase.setTexture(texture);
	m_tankBase.setScale(sf::Vector2f(100, 200)); // Corrected line

	m_tankBase.setTextureRect(sf::IntRect(0, 118, 246, 114));
	m_tankBase.setOrigin(80,50);


	//m_tankBase.setOrigin(123, 116);
}
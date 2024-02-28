#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Tank.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "ScreenSize.h"
#include <Thor/Resources.hpp>
#include<LevelLoader.h>
#include "CollisionDetector.h"
/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
/// 
/// 

class Tank
{
public:	
	double m_speed = { 0 };
	double m_rotation{ 0.0 };
	double m_turretRotation{0.0};
	double secondCounter = 60;
	double bulletRotation;

	/// <summary> /// @brief Constructor that stores drawable state (texture, sprite) for the /// tank. /// Stores references to the resource holder and container of wall sprites. /// Creates sprites for the tank base and turret from the texture in the
	/// resource holder. /// </summary> /// <param name="t_holder">A reference to the resource holder</param> ///< param name="t_wallSprites">A reference to the container of wall
	/// sprites </param> 
	Tank(thor::ResourceHolder <sf::Texture, std::string> & t_holder,
	std::vector<sf::Sprite>& t_wallSprites);
	std::vector<sf::Sprite>& m_wallSprites;
	bool reloading = false;
	sf::Vector2f  m_contactNormal;
	float m_dt;
	void update(double dt);
	void render(sf::RenderWindow & window);
	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();
	sf::Vector2f deflectVector;
	void fire();
	void setScale(sf::Vector2f t_scale);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	int MAX_REVERSE_SPEED = -400;
	int MAX_FORWARD_SPEED = 400;
	int MIN_TURRET_ROTATION = -100;
	int MAX_TURRET_ROTATION = 100;
	void handleKeyInput();
	void increaseTurretRotation();
	void decreaseTurretRotation();
	void centreTurret();
	/// <summary> /// @brief Checks for collisions between the tank and the walls. /// /// </summary> /// <returns>True if collision detected between tank and wall.</returns>
	/// <summary>
	/// @brief Basic collision response algorithm. Uses a pre-calculated /// contact normal to deflect the tank in the event of a base/wall or /// turret/wall collision.
	/// </summary>
	void deflect();
private:
	bool m_shouldRotateTurret{ false };
	double m_initialTurretRotation{ 0.0 };
	double m_destTurretRotation{ 0.0 };
	int m_rotationDirection{ 1 };  // 1 for clockwise, -1 for counterclockwise
	void initSprites();
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Sprite m_bulletSprite;
	int bulletCounter=0;
	int bulletSpeed = 1000;


	thor::ResourceHolder<sf::Texture, std::string> & m_holder;
		
};

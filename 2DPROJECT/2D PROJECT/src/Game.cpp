#include "Game.h"
#include <iostream>
#include"Turret.h"
// Our target FPS
static double const FPS{ 60.0f };

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width,

		ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)

	, m_tank(m_holder, m_wallSprites), m_turretTargets()
{


	init();
}


void Game::generateWalls(sf::Texture& m_texture)
{
	// Replace the ? With the actual values for the wall image 
	sf::IntRect wallRect(0, 95, 32, 22); // Create the Walls 
	for (auto const& obstacle : m_level.m_obstacles) {
		sf::Sprite sprite; sprite.setTexture(m_texture); 
		sprite.setTextureRect(wallRect); 
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0); 
		sprite.setPosition(obstacle.m_position); 
		sprite.setRotation(obstacle.m_rotation); 
		m_wallSprites.push_back(sprite);
	}
}


////////////////////////////////////////////////////////////
void Game::init()
{
	


	m_countdownSeconds = 60.0f;

	m_timerText.setFont(m_arialFont);
	m_timerText.setPosition(20, 20); // Adjust the position as needed
	m_timerText.setCharacterSize(24);
	m_timerText.setFillColor(sf::Color::White);


	int currentLevel = 1;
	
	try { LevelLoader::load(currentLevel, m_level); }
	catch (std::exception& e) { std::cout << "Level Loading failure." << std::endl; std::cout << e.what() << std::endl; throw e; }
	// Really only necessary is our target FPS is greater than 60.
	m_window.setVerticalSyncEnabled(true);

	if (!m_arialFont.loadFromFile("BebasNeue.otf"))
	{
		std::cout << "Error loading font file";
	}

	sf::Texture& bgTexture = m_holder["bgSprite"];
	m_bgSprit.setTexture(bgTexture);

	m_tank.setPosition(m_level.m_tank.m_position);

	m_tank.setScale(m_level.m_tank.m_scale);


	generateWalls(m_holder["tankAtlas"]);
	for (int i = 0; i < 4; i++) {
		m_turretTargets[i].setPos(m_level.m_turretData[i].m_position.x, m_level.m_turretData[i].m_position.y);
		m_turretTargets[i].setFireFreq(1);

	}

#ifdef TEST_FPS
	x_updateFPS.setFont(m_arialFont);
	x_updateFPS.setPosition(20, 300);
	x_updateFPS.setCharacterSize(24);
	x_updateFPS.setFillColor(sf::Color::White);
	x_drawFPS.setFont(m_arialFont);
	x_drawFPS.setPosition(20, 350);
	x_drawFPS.setCharacterSize(24);
	x_drawFPS.setFillColor(sf::Color::White);
#endif
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asMilliseconds()); //60 fps
#ifdef TEST_FPS
			x_secondTime += timePerFrame;
			x_updateFrameCount++;
			if (x_secondTime.asSeconds() > 1)
			{
				std::string updatesPS = "UPS " + std::to_string(x_updateFrameCount - 1);
				x_updateFPS.setString(updatesPS);
				std::string drawsPS = "DPS " + std::to_string(x_drawFrameCount);
				x_drawFPS.setString(drawsPS);
				x_updateFrameCount = 0;
				x_drawFrameCount = 0;
				x_secondTime = sf::Time::Zero;
			}
#endif
		}
		render(); // as many as possible
#ifdef TEST_FPS
		x_drawFrameCount++;
#endif
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;

		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	m_tank.update(dt);
	sf::Vector2 pos=m_tank.getPosition();
	for (int i = 0; i < 4; ++i) {
		m_turretTargets[i].update(dt, pos,m_window);
	}
	// Update the countdown timer
	sf::Time elapsed = m_timerClock.restart();
	m_countdownSeconds -= elapsed.asSeconds();

	// Check if the countdown has reached zero
	if (m_countdownSeconds <= 0.0f)
	{
		// Game over or any other necessary actions
		// For now, let's close the window
		m_window.close();
	}

	// Update other game logic as needed
}

////////////////////////////////////////////////////////////
void Game::render()
{

	m_window.clear(sf::Color(0, 0, 0, 0));
#ifdef TEST_FPS
	m_window.draw(m_bgSprit);
	for (int i = 0; i < m_level.m_obstacles.size(); i++) {
		m_window.draw(m_wallSprites[i]);
	}
	m_timerText.setString("Time: " + std::to_string(static_cast<int>(m_countdownSeconds)));
	m_tank.render(m_window);
	for (int i = 0; i < 4; i++) {
		m_turretTargets[i].draw(m_window);

	}
	m_window.draw(m_timerText);
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}






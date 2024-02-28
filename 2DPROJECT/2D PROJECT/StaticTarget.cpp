#include "Target.h"
#include"MathUtility.h"
#include <Thor/Resources.hpp>
StaticTarget::StaticTarget(thor::ResourceHolder<sf::Texture, std::string>& t_holder,

	std::vector<sf::Sprite>& t_wallSprites)

	: m_holder(t_holder),

	m_wallSprites(t_wallSprites)

{
	initSprites();

}



double DEG_TO_RAD = std::numbers::pi / 180.0f;
void StaticTarget::update(double dt)
{


}

void StaticTarget::render(sf::RenderWindow& window)
{

}



void StaticTarget::initSprites()
{


}


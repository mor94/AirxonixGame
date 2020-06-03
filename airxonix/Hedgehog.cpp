#include "Hedgehog.h"
#include "MyFactory.h"

//===================================================================================
//constructor
Hedgehog::Hedgehog()
	:Enemy(Media::instance().getTexture(t_hedgehog))
{
	startPosition = { ((rand() % BOARD_SIZE)),((rand() % BOARD_SIZE)) };
	setObjectPositionStart(startPosition);
	m_angle = { 0,0 };
	
}

//===================================================================================
//this function restart the object position to his start position
void Hedgehog::reset()
{
	setObjectPositionStart(startPosition);

}

//===================================================================================
//this function return the start position
sf::Vector2i Hedgehog::getStartIndex()
{
	return startPosition;
}

//===================================================================================
//register
bool Hedgehog::m_registerit = MyFactory::registerit(t_hedgehog,
	[]() -> std::unique_ptr<Enemy> { return std::make_unique<Hedgehog>(); });

//===================================================================================
//draw the object
void Hedgehog::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//==========================================================================
//mange the movement
void Hedgehog::move(sf::Vector2i index)
{
	m_sprite.setPosition((sf::Vector2f)(index));
	if (clock.getElapsedTime().asSeconds() >= time.asSeconds())
	{
		changeDir();
		clock.restart();
	}
}
//==========================================================================
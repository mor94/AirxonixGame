#include "WreckingBall.h"
#include "MyFactory.h"

//=================================================================================
//constructor
WreckingBall::WreckingBall()
	:Ball(Media::instance().getTexture(t_wreckingBall))
{
	
	startPosition = { (((rand() % (BOARD_SIZE - 2)) + 1)*PICSIZE) ,(((rand() % (BOARD_SIZE - 2)) + 1)*PICSIZE) };
	setObjectPositionStart(startPosition);
}
//=================================================================================
//register
bool WreckingBall::m_registerit = MyFactory::registerit(t_wreckingBall,
	[]() -> std::unique_ptr<Enemy> { return std::make_unique<WreckingBall>(); });
//=================================================================================
//return the start position
sf::Vector2i WreckingBall::getStartIndex()
{
	return startPosition;
}

//=================================================================================
//reset the position to the start position
void WreckingBall::reset()
{
	setObjectPositionStart(startPosition);
}
//=================================================================================
//draw the object
void WreckingBall::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//=================================================================================
//move the sprite
void WreckingBall::move(sf::Vector2i index)
{
	setObjectPosition(index);
}
//=================================================================================

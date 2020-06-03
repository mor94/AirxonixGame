#include "RegularBall.h"
#include "MyFactory.h"

//=================================================================================
//constructor
RegularBall::RegularBall()
	:Ball(Media::instance().getTexture(t_regularBall))
{
	startPosition = { (rand() % (BOARD_SIZE - 2)+1)*PICSIZE,(rand() % (BOARD_SIZE - 2) + 1)*PICSIZE };
	setObjectPositionStart(startPosition );
}
//=================================================================================
//register
bool RegularBall::m_registerit = MyFactory::registerit(t_regularBall,
	[]() -> std::unique_ptr<Enemy> { return std::make_unique<RegularBall>(); });

//=================================================================================
//return the start position
sf::Vector2i RegularBall::getStartIndex()
{
	return startPosition;
}

//=================================================================================
//reset the position to the start position
void RegularBall::reset()
{
	setObjectPositionStart(startPosition);
}
//=================================================================================
//draw the object
void RegularBall::draw(sf::RenderWindow & window)
{
	
	window.draw(m_sprite);
}
//=================================================================================
//move the sprite
void RegularBall::move(sf::Vector2i index)
{
	setObjectPosition(index);
}
//=================================================================================

#include "Prize.h"


//=================================================================================
//constractor
Prize::Prize(sf::Texture & type)
	:Object(type)
{
	sf::Vector2i pos = { (rand() % (BOARD_SIZE - 2) + 1)*PICSIZE,(rand() % (BOARD_SIZE - 2) + 1)*PICSIZE };
	setObjectPositionStart(pos);
}
//===================================================================================
//draw the prize
void Prize::draw(sf::RenderWindow  & window)
{
	window.draw(m_sprite);
}
//===================================================================================
//return the clock
sf::Clock Prize::getClock()
{
	return prize_clock;
}
//===================================================================================
//return the time
sf::Time Prize::getTime()
{
	return prize_time;
}
//===================================================================================


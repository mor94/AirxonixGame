#include "Helicopter.h"


//=======================================================================================
//constructor
Helicopter::Helicopter()
	:DynamicObject(Media::instance().getTexture(t_helicopter))
	, m_life(LIFES),m_speed(SPEED), emptyArea(false),closeArea(false),canMove(false)
	,dir(t_wait),m_score(0)
{
	startPosition = { (BOARD_SIZE / 2)*PICSIZE , (BOARD_SIZE - 1)*PICSIZE };
	setObjectPositionStart(startPosition);
}
//=======================================================================================
//this function set the position to the start position
void Helicopter::setHelicopterPosition()
{
	setObjectPositionStart(startPosition);
}
//=======================================================================================
void Helicopter::reset()
{
	setObjectPositionStart(startPosition);
}
//=======================================================================================
//this function return the start position
 sf::Vector2i Helicopter::getStartIndex()
{
	 return startPosition;
}
 //=======================================================================================
//this function update the life
void Helicopter::setLife(int val)
{
	if (val == -1)
		m_life--;
	else
	{
		m_life++;
	}
}
//=======================================================================================
//return the life
int Helicopter::getLife()
{
	return m_life;
}
//=======================================================================================
//draw the object
void Helicopter::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//=======================================================================================
//move the object
void Helicopter::move(sf::Vector2i newPosition)
{
		setObjectPosition(newPosition);
}
//=======================================================================================
//return if the helicopter on empty area
bool Helicopter::getEmptyArea()
{
	return emptyArea;
}
//=======================================================================================
//set the helicopter position- empty area or full area
void Helicopter::setEmptyArea(bool b)
{
	emptyArea = b;
}
//=======================================================================================
//return if the helicopter on empty area
bool Helicopter::getCloseArea()
{
	return closeArea;
}
//=======================================================================================
//set if the helicopter on empty area
void Helicopter::setCloseArea(bool b)
{
	closeArea = b;
}
//=======================================================================================
//return the score
int Helicopter::getScore()
{
	return m_score;
}
//=======================================================================================
//set the score
void Helicopter::setScore(int num)
{
	m_score += num;
}
//=======================================================================================

#include "Ball.h"


//================================================================
//constractor
Ball::Ball(sf::Texture & type)
	:Enemy(type)
{
	setIncline(); //set the ball angle
}
//=======================================================================
//this function change the angle of the ball
void Ball::setIncline()
{

	int x = rand() % 3;
	int y = rand() % 3;
	if (x == 0)
		m_angle.x = -PICSIZE;
	else if (x == 2)
		m_angle.x = PICSIZE;
	else
		m_angle.x = 0;
	if (y == 0)
		m_angle.y = -PICSIZE;
	else if (y == 2)
		m_angle.y = PICSIZE;
	else
	{
		if (m_angle.x != 0)
			m_angle.y = 0;
		else
			m_angle.y = PICSIZE;
	}
		
}
//================================================================

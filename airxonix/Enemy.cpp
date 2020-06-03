#include "Enemy.h"

//========================================================================
//constructor
Enemy::Enemy(sf::Texture & type)
	:DynamicObject(type)
{
	dir = rand() % 4 + 1;
}

//==========================================================================
sf::Vector2i Enemy::getAngle()
{
	return m_angle;
}
//==========================================================================

void Enemy::changeDir()
{
	dir = rand() % 4 + 1;
}
//==========================================================================

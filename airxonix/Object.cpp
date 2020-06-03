#include "Object.h"


//=================================================================
//constructor
Object::Object(sf::Texture & type)
{
	m_sprite.setTexture(type);
}
//=================================================================
//set the position of the sprite
void Object::setObjectPosition(sf::Vector2i position)
{
	sf::Vector2f pix;
	pix.x =(float) position.x ;
	pix.y =(float) position.y;
	m_sprite.setPosition(pix);
}
//=================================================================
//set the start position of the sprite- for the shift
void Object::setObjectPositionStart(sf::Vector2i position)
{
	sf::Vector2f pix;
	pix.x = (float)position.x +SHIFT;
	pix.y = (float)position.y;
	m_sprite.setPosition(pix);
}
//=================================================================
//return the sprite
sf::Sprite & Object::getSprite()
{
	return m_sprite;
}
//=======================================================================================



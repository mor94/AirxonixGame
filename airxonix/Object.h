#pragma once
#include "Media.h"
#include <iostream>
class Hedgehog;
class Helicopter;
class RegularBall;
class WreckingBall;
class EmptyCell;
class FullCell;
class Line;


class Object
{
public:
	Object(sf::Texture & type);
	virtual void draw(sf::RenderWindow & window) = 0;
	void setObjectPosition(sf::Vector2i position);
	void setObjectPositionStart(sf::Vector2i position);
	sf::Sprite & getSprite();

protected:
	sf::Sprite m_sprite;
};


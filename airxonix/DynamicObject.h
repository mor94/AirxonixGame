#pragma once
#include "Object.h"
class DynamicObject:public Object
{
public:
	DynamicObject(sf::Texture & type);
	virtual void move(sf::Vector2i index)=0;
	virtual sf::Vector2i getStartIndex()=0;
	virtual void reset() = 0;

protected:
	sf::Vector2i startPosition;
};


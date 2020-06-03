#pragma once
#include "Enemy.h"
#include <time.h>
const float pi = 3.14159f;
class Ball: public Enemy
{
public:
	Ball(sf::Texture & type);
	virtual void move(sf::Vector2i index)=0 ;
	virtual sf::Vector2i getStartIndex() = 0;
	virtual void reset() = 0;
	 void setIncline();
	
protected:
	
};


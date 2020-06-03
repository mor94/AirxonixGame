#pragma once
#include "Ball.h"

class MyFactory;

class RegularBall: public Ball
{
public:
	RegularBall();
	void move(sf::Vector2i index);
	void draw(sf::RenderWindow & window);
	virtual sf::Vector2i getStartIndex();
	virtual void reset();

private:
	static bool m_registerit;
};


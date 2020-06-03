#pragma once
#include "Ball.h"
class MyFactory;

class WreckingBall: public Ball
{
public:
	WreckingBall();
	void move(sf::Vector2i index);
	void draw(sf::RenderWindow & window);
	void setEnemyPosition(sf::Vector2i position);
	virtual sf::Vector2i getStartIndex() ;
	virtual void reset() ;
	//void setIncline();
private:
	static bool m_registerit;
	
};


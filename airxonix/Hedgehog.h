#pragma once
#include "Enemy.h"
class MyFactory;
class Hedgehog :public Enemy
{
public:
	Hedgehog();
	void move(sf::Vector2i index);
	 void draw(sf::RenderWindow & window) ;
	 virtual sf::Vector2i getStartIndex();
	 virtual void reset();

private:
	static bool m_registerit;
	sf::Clock clock;
	sf::Time time = sf::seconds(5);
};


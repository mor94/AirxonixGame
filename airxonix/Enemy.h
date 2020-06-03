#pragma once

#include "DynamicObject.h"
class Enemy:public DynamicObject
{
public:
	Enemy(sf::Texture & type);
	virtual void move(sf::Vector2i index) = 0;
	virtual void draw(sf::RenderWindow & window)=0;
	virtual sf::Vector2i getStartIndex() = 0;
	sf::Vector2i getAngle();
	virtual void reset() = 0;
	int getDir() { return dir; }
	void changeDir();
private:
protected:
	sf::Vector2i m_angle;
	int dir;

};


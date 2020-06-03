#pragma once
#include "DynamicObject.h"

#define LIFES 3
#define SPEED 5
class Helicopter:public DynamicObject
{
public:
	Helicopter();
	void draw(sf::RenderWindow & window);
	void setLife(int val);
	int getLife();
	void setHelicopterPosition();
	sf::Vector2i getStartIndex();
	void reset() ;
	void move(sf::Vector2i newPosition);
	bool getEmptyArea();
	void setEmptyArea(bool b);
	bool getCloseArea();
	void setCloseArea(bool b);
	void setDir(direction new_dir) { dir = new_dir; }
	direction getDir() { return dir; }
	void setMove(bool b) { canMove = b; }
	bool getCanMove() { return canMove; }
	int getScore();
	void setScore(int num);
private:
	int m_life;
	float m_speed;
	bool emptyArea;
	bool closeArea;
	int m_score;
	direction dir;
	bool canMove;


};


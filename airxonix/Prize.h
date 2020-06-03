#pragma once
#include "MyEnum.h"
#include "Media.h"
#include "Object.h"
class Prize :public Object
{
public:
	Prize(sf::Texture & type);
	void draw(sf::RenderWindow & window);
	sf::Clock getClock();
	sf::Time getTime();
	//void playSound();
protected:
	sf::Vector2i position;
	sf::Clock prize_clock;
	sf::Time prize_time = sf::seconds(15);
	sf::Sound  m_sound;
};


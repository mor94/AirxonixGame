#pragma once
#include "Command.h"
class HighScore :public Command
{
public:
	HighScore();
	virtual void execute(sf::RenderWindow & m_window);	
private:
	std::map<std::string, unsigned int> highScore;
	sf::Sprite m_sprite;
};


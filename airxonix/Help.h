#pragma once
#include "Command.h"
class Help :public Command
{
public:
	Help();
	virtual void execute(sf::RenderWindow & m_window);
private:
	sf::Sprite m_sprite;
};


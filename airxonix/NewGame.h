#pragma once
#include "Command.h"
class NewGame:public Command
{
public:
	virtual void execute(sf::RenderWindow & m_window);
private:
	sf::Sound sound_extraLife;
};


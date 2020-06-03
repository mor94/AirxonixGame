#pragma once
#include "Command.h"

class Exit: public Command
{
public:
	virtual void execute(sf::RenderWindow & m_window);
};


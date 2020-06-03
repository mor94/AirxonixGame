#pragma once
#include "Game.h"
#include <iostream>
class Command
{
public:

	virtual void execute(sf::RenderWindow & m_window) = 0;
};


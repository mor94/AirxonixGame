#pragma once
#include "CellMode.h"
class CloseCell:public CellMode
{
public:
	CloseCell();
	void draw(sf::RenderWindow & window);
};


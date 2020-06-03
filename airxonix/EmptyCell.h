#pragma once
#include "CellMode.h"
class EmptyCell :public CellMode
{
public:
	EmptyCell();
	void draw(sf::RenderWindow & window);


};


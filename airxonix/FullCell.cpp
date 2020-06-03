#include "FullCell.h"


//===================================================================================
//constructor
FullCell::FullCell()
	:CellMode(Media::instance().getTexture(t_fullCell))
{
}

//===================================================================================
//draw the cell
void FullCell::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//===================================================================================

#include "CloseCell.h"


//=================================================================================
//constractor
CloseCell::CloseCell()
	:CellMode(Media::instance().getTexture(t_emptyCell))
{
}
//=================================================================================
//draw the object
void CloseCell::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//===================================================================================

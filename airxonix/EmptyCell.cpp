#include "EmptyCell.h"


//================================================================
//constructor
EmptyCell::EmptyCell()
	:CellMode(Media::instance().getTexture(t_emptyCell))
{
}
//========================================================================
//draw the cell
void EmptyCell::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//================================================================

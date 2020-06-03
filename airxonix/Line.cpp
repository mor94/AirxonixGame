#include "Line.h"


//==================================================================
//constructor
Line::Line()
	:CellMode(Media::instance().getTexture(t_line))
{
}
//==================================================================
//draw the object
void Line::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//=======================================================================================

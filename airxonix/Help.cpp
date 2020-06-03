#include "Help.h"


//================================================================
//constructor
Help::Help()
{
	m_sprite.setTexture((Media::instance().getTexture(t_helpScreen)));

}
//================================================================
//this function are action the help button
void Help::execute(sf::RenderWindow & m_window)
{
	sf::Event event;
	m_window.draw(m_sprite);
	m_window.display();
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	return;
}
//================================================================

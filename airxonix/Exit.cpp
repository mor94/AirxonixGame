#include "Exit.h"

//this function are action the exit button
void Exit::execute(sf::RenderWindow & m_window)
{
	Media::instance().playSound(t_ByeByeSound);
	Media::instance().moveToFile();
	m_window.close();
}
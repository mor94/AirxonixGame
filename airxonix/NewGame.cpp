#include "NewGame.h"

//================================================================
//this function are action the new game score button
void NewGame::execute(sf::RenderWindow & m_window)
{
	Game game(m_window);
	
	//sound_start.play();
	game.run();
	

}
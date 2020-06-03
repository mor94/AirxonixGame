#include "HighScore.h"
#include <sstream>

//=================================================================================
//constructor
HighScore::HighScore()
{
	m_sprite.setTexture(Media::instance().getTexture(t_highScoreBackground));

}
//================================================================
//this function are action the high score button
void HighScore::execute(sf::RenderWindow & m_window)
{

	int place = 0;
	sf::Text text;
	text.setFont(Media::instance().get_font());
	std::multimap<unsigned int, std::string> & highScore_table = Media::instance().getHighScore();
	std::multimap<unsigned int, std::string>::reverse_iterator it;
	m_window.clear();
	m_window.draw(m_sprite);
	for (it = highScore_table.rbegin(); it != highScore_table.rend(); ++it, place++)
	{
		text.setString(it->second + " " + std::to_string(it->first));
		text.setPosition({ 300.f,(50.f*place) + 300.f });
		m_window.draw(text);
	}
	m_window.display();
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
}

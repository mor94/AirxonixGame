#include "Menu.h"


//=================================================================================
//constructor
Menu::Menu()
{
	m_window.create(sf::VideoMode(1300, 700), "Airxonix");
	createMenu();
	Media::instance().createHighScore();
}

//=================================================================================
//this function add the buttons
void Menu::add()
{
	m_options.emplace_back(std::make_unique<NewGame>());
	m_options.emplace_back(std::make_unique<Help>());
	m_options.emplace_back(std::make_unique<HighScore>());
	m_options.emplace_back(std::make_unique<Exit>());
}
//=================================================================================
//this function active the buttons
void Menu::active()
{
	add();
	sf::Event event;
	(Media::instance().playSound(t_welcomeSound));

	while (m_window.isOpen())
	{
		show();
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonReleased)
			{
				Media::instance().playSound(t_clickSound);
				myEnum option = getOptionFromUser(event);
				perform(option);
			}
		}
	}

}
//=================================================================================
//this function create the menu
void Menu::createMenu()
{
	
	sprite_background.setTexture(Media::instance().getTexture(t_menuBackground));
	sprite_help.setTexture(Media::instance().getTexture(t_help));
	sprite_highScore.setTexture(Media::instance().getTexture(t_highScore));
	sprite_newGame.setTexture(Media::instance().getTexture(t_newGame));
	sprite_exit.setTexture(Media::instance().getTexture(t_exit));

	sprite_newGame.setPosition({ 540,90 });
	sprite_highScore.setPosition({ 540,250 });
	sprite_help.setPosition({ 550,400 });
	sprite_exit.setPosition({ 550,560 });
	sprite_background.setPosition({ 0,0 });

}
//=================================================================================
//this function show the menu
void Menu::show()
{
	m_window.clear();
	m_window.draw(sprite_background);
	m_window.draw(sprite_newGame);
	m_window.draw(sprite_help);
	m_window.draw(sprite_highScore);
	m_window.draw(sprite_exit);
	m_window.display();
}
//=================================================================================
//this function return the enum are the user press
myEnum Menu::getOptionFromUser(sf::Event event)
{

	if(sprite_newGame.getGlobalBounds().contains({ (float)event.mouseButton.x,(float)event.mouseButton.y }))
		return t_newGame;
	if (sprite_help.getGlobalBounds().contains({ (float)event.mouseButton.x,(float)event.mouseButton.y }))
		return t_help;
	if (sprite_highScore.getGlobalBounds().contains({ (float)event.mouseButton.x,(float)event.mouseButton.y }))
		return t_highScore;
	if (sprite_exit.getGlobalBounds().contains({ (float)event.mouseButton.x,(float)event.mouseButton.y }))
		return t_exit;
}
//=================================================================================
//this function active the button
void Menu::perform(myEnum option)
{
	m_options[option]->execute(m_window);
}
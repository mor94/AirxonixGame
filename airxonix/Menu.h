#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Command.h"
#include <vector>
#include "NewGame.h"
#include "HighScore.h"
#include "Help.h"
#include "Exit.h"
#include "Media.h"
using namespace std;


class Menu
{
public:
	Menu();
	void add();
	void active();
private:
	sf::RenderWindow m_window;
	vector<std::unique_ptr<Command>> m_options;

	void show();
	myEnum getOptionFromUser(sf::Event event);
	void perform(myEnum option);
	void createMenu();

	sf::Sprite sprite_background;
	sf::Sprite sprite_newGame;
	sf::Sprite sprite_exit;
	sf::Sprite sprite_highScore;
	sf::Sprite sprite_help;

	sf::Sound soudWelcome;

};


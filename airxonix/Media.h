#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include "MyEnum.h"
#include <memory>
#include <sstream>

class Enemy;

class Media
{
public:
	static Media& instance();
	sf::Texture & getTexture(myEnum type);
	sf::Font & get_font();
	std::fstream & getFile();
	sf::SoundBuffer & getSound(sounds type);
	static std::map<myEnum, std::unique_ptr<Enemy>(*)()> & getMap();
	std::multimap<unsigned int, std::string> & getHighScore();
	void playSound(sounds type);

	void createHighScore();
	void moveToFile();
	void closeFile();
private:
	Media();
	Media (Media&) = delete;
	std::vector<sf::Texture> vec_texture;
	/*sf::Texture texture_menuBackground;
	sf::Texture texture_newGame;
	sf::Texture texture_exit;
	sf::Texture texture_highScore;
	sf::Texture texture_help;
	sf::Texture texture_helicopter;
	sf::Texture texture_regularBall;
	sf::Texture texture_wreckingBall;
	sf::Texture texture_hedgehog;
	sf::Texture texture_emptyCell;
	sf::Texture texture_fullCell;
	sf::Texture texture_line;
	sf::Texture texture_background;
	sf::Texture texture_heart;
	sf::Texture texture_clock;
	sf::Texture texture_board;
	sf::Texture texture_levelUpBack;

	sf::Texture texture_boostPrize;
	sf::Texture texture_lifePrize;
	sf::Texture texture_poisionPrize;
	sf::Texture texture_timePrize;
	sf::Texture texture_coinPrize;
	
	sf::Texture texture_HelpScreen;
*/
	sf::Texture text;
	sf::Font font;

	std::fstream highScore;

	std::vector<sf::SoundBuffer> buffer_vec;
	sf::Sound m_sound;

	//sf::SoundBuffer sound_welcome;
	//sf::SoundBuffer sound_start;
	//sf::SoundBuffer sound_line;
	//sf::SoundBuffer sound_lifePrize;
	//sf::SoundBuffer sound_scorePrize;
	//sf::SoundBuffer sound_poisionPrize;
	//sf::SoundBuffer sound_timePrize;
	//sf::SoundBuffer sound_frozenPrize;
	//sf::SoundBuffer sound_ball;
	//sf::SoundBuffer sound_heli;
	//sf::SoundBuffer sound_no;

	std::multimap<unsigned int, std::string> highScore_table;

	//std::map<myEnum, sf::Sprite> m_object;
	void createMap();
	
};


#pragma once
#include "Helicopter.h"
#include "Enemy.h"
#include "Media.h"
#include "MyFactory.h"
#include"PrizeFactory.h"
#include "Level.h"
#include "Board.h"
#include <map>
#include <fstream>

#define CREATE_PRIZE 10000
#define NUM_OF_PRIZES 5

class Game
{
public:
	Game(sf::RenderWindow & window);
	bool run();
	void setHelicopterLife(int val);
	void moveHeli();
	void reset();
	void moveBalls();
	void moveHedgehog();
	void setBoard(std::unique_ptr<CellMode>, sf::Vector2i index);
	void eatWall(sf::Vector2i index);
	bool checkLimits(sf::Vector2i position);
	void insertToMap(unsigned int score, std::string name);
	void closeFile();
	void setFrozenPrize(bool value);
	void setPoisionScreen(bool value);
	bool getFrozenPrize();
	void restartFrozenPrizeClock();
	void restartPoisionPrizeClock();
	void setTimeOfLevel(int secondes);
private:
	sf::RenderWindow &  m_window;
	std::unique_ptr<Helicopter> m_heli;
	std::vector <std::unique_ptr <Enemy>> m_balls;
	std::vector <std::unique_ptr <Enemy>> m_hedgehogs;
	std::vector <std::unique_ptr <Prize>> m_prizes;
	std::map <unsigned int, sf::String>  highScores;
	Level m_level;
	Board m_board;
	bool frozen_prize;
	bool poision_screen;
	bool runningOutTime;
	int current_percentage;
	sf::Clock heli_clock;
	sf::Time heli_time = sf::seconds(0.1);
	sf::Clock enemy_clock;
	sf::Time enemy_time = sf::seconds(0.3);
	sf::Clock level_clock;
	sf::Time level_time = sf::seconds(120);
	sf::Clock prizeFrozen_clock;
	sf::Time prizeFrozen_time = sf::seconds(5);
	sf::Clock prizePoision_clock;
	sf::Time prizePoision_time = sf::seconds(5);
	std::fstream  & highScore;
	sf::Sprite sprite_background;
	sf::Sprite sprite_heart;
	sf::Sprite sprite_clock;
	sf::Sprite sprite_board;
	sf::Sprite sprite_poisionScreen;
	sf::Sprite sprite_levelUpScreen;
	sf::Text life_text;
	sf::Text level_text;
	sf::Text percent_text;
	sf::Text clock_text;
	sf::Text score_text;

	sf::Music music_background;
	sf::Sound sound_start;
	sf::Sound sound_line;

	float time_of_level;
	void gameOver();
	void createBoard();
	void createObject();
	void useFactory(myEnum type, int num);
	void drawObjects();
	void newLevel();
	void collisionMove(sf::Vector2i new_pos);
	void closeArea();
	void drop(sf::Vector2i enemy_pos);
	void levelUpScreen();
	void createPrize();
	void youWin();
	void showImages();
	void setImages();
	sf::Vector2i findIndexByKey();
	sf::Vector2i findIndexbyDir(sf::Vector2i);
};


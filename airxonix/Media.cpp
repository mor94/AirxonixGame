#include "Media.h"
#include "Enemy.h"
 
std::map<myEnum, std::unique_ptr<Enemy>(*)()> m_map;
//===================================================================================
//this class is using the design pattern singleton 
Media::Media()
{
	
	buffer_vec.resize(t_MAX_SOUND);
	vec_texture.resize(t_MAX_texture);
	vec_texture[t_newGame].loadFromFile("new game.png");
	vec_texture[t_help].loadFromFile("help.png");
	vec_texture[t_highScore].loadFromFile("high scores.png");
	vec_texture[t_exit].loadFromFile("exit.png");
	vec_texture[t_timePrize].loadFromFile("timePrize.png");
	vec_texture[t_lifePrize].loadFromFile("heartPrize.png");
	vec_texture[t_poisionPrize].loadFromFile("poisionPrize.png");
	vec_texture[t_boostPrize].loadFromFile("frozenPrize.png");
	vec_texture[t_coinPrize].loadFromFile("Coin.png");
	vec_texture[t_menuBackground].loadFromFile("menu_back3.png");
	vec_texture[t_helicopter].loadFromFile("heli1.png");
	vec_texture[t_wreckingBall].loadFromFile("wrecking ball.png");
	vec_texture[t_regularBall].loadFromFile("regular ball.png");
	vec_texture[t_hedgehog].loadFromFile("hedgehog.png");
	vec_texture[t_fullCell].loadFromFile("metal4.jpg");
	vec_texture[t_emptyCell].loadFromFile("stars.jpg");////
	vec_texture[t_line].loadFromFile("line1.png");
	vec_texture[t_background].loadFromFile("back4.jpg");
	vec_texture[t_board].loadFromFile("board2.jpg");
	vec_texture[t_heart].loadFromFile("heart.png");
	vec_texture[t_clock].loadFromFile("clock3.png");
	vec_texture[t_helpScreen].loadFromFile("helpscreen.png");
	vec_texture[t_levelUpScreen].loadFromFile("level up.png");
	vec_texture[t_highScoreBackground].loadFromFile("highScoreScreen.png");
	vec_texture[t_poisionScreen].loadFromFile("poisionScreen.png");
	vec_texture[t_gameOverBackground].loadFromFile("GameOver.png");
	vec_texture[t_youWinBackground].loadFromFile("youWin.png");

	highScore.open("highScore.txt");

	font.loadFromFile("myfont.ttf");
	buffer_vec[t_welcomeSound].loadFromFile("WelcomeSound.wav");
	buffer_vec[t_startSound].loadFromFile("StartSound.wav");
	buffer_vec[t_lineSound].loadFromFile("LineSound.wav");
	buffer_vec[t_lifePrizeSound].loadFromFile("LifeSound.wav");
	buffer_vec[t_scorePrizeSound].loadFromFile("BonusSound.wav");
	buffer_vec[t_timePrizeSound].loadFromFile("TimeSound.wav");
	buffer_vec[t_poisionPrizeSound].loadFromFile("PoisionSound.wav");
	buffer_vec[t_frozenPrizeSound].loadFromFile("freezeSound.wav");
	buffer_vec[t_gameOverSound].loadFromFile("GameOverSound.wav");
	buffer_vec[t_ByeByeSound].loadFromFile("ByeByeSound.wav");
	buffer_vec[t_clickSound].loadFromFile("ClickSound.wav");
	buffer_vec[t_OoSound].loadFromFile("OoSound.wav");
	buffer_vec[t_OoSound].loadFromFile("OhySound.wav");
	buffer_vec[t_closeAreaSound].loadFromFile("CloseAreaSound.wav");
	buffer_vec[t_runningOutTimeSound].loadFromFile("RunningOutTimeSound.wav");

}
//===================================================================================

Media& Media::instance()
{
	static Media m_media;
	return m_media;
}
//===================================================================================
void Media::playSound(sounds type)
{

		m_sound.setBuffer(buffer_vec[type]);
		m_sound.play();
	
}
//===================================================================================
std::map<myEnum, std::unique_ptr<Enemy>(*)()> & Media::getMap()
{
	static std::map<myEnum, std::unique_ptr<Enemy>(*)()> m_map;
	return m_map;
}
//===================================================================================

sf::Texture & Media::getTexture(myEnum type)
{
	return vec_texture[type];

}
//===================================================================================
sf::Font & Media::get_font()
{
	return font;
}
//===================================================================================
std::fstream & Media::getFile()
{
	return highScore;
}
//===================================================================================
void  Media::createHighScore()
{
	highScore.open("highScore.txt");
	std::stringstream ss;
	unsigned int score;
	std::string name;
	ss << highScore.rdbuf();
	do
	{
		std::string temp;
		ss >> score >> name;
		if (name != temp)
		{
			highScore_table.emplace(score, name);
			name = temp;
		}
		else
			break;

	} while (!ss.eof());
	highScore.close();
	std::remove("highScore.txt");

}
//===================================================================================
void Media::moveToFile()
{
	highScore.open("highScore.txt", std::ios::in | std::ios::out | std::ios::trunc);
	if (highScore.is_open())
		for (auto it = highScore_table.begin(); it != highScore_table.end(); it++)
		{
			highScore << (*it).first << " " << (*it).second << "\n";
		}

}
//===================================================================================
void Media::closeFile()
{
	highScore.close();
}
//===================================================================================
std::multimap<unsigned int, std::string> & Media::getHighScore()
{
	return highScore_table;
}
//===================================================================================
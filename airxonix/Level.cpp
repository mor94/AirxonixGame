#include "Level.h"


//================================================================================
//constructor
Level::Level(int level)
	:m_level(level)
{
	open_file();
	insert_data();
}

//================================================================================
//this function open the file of the level
void Level::open_file()
{
	switch (m_level)
	{
	case 1:
		m_file.open("level1.txt");
		break;
	case 2:
		m_file.open("level2.txt");
		break;
	case 3:
		m_file.open("level3.txt");
		break;
	}
	if (!m_file)
	{
		std::cout << "Problem opening file";
		exit(EXIT_FAILURE);
	}
}
//================================================================================
//this function insert data 
void Level::insert_data()
{
	std::string value;
	for (int i = 0; i < 4; i++)
	{
		getline(m_file, value);
		if (i == 3)
		{
			m_percent = stoi(value);
		}
		else
			num_of_enemys.push_back(stoi(value));
	}	
}
//================================================================================
//this function return how many regullar ball in the level
int Level::getNumOfRegularBall()
{
	return num_of_enemys[0];
}
//================================================================================
//this function return how many wrecking ball in the level
int Level::getNumOfWreckingBall()
{
	return num_of_enemys[1];
}
//================================================================================
//this function return how many hedgehog in the level
int Level::getNumOfHedgehog()
{
	return num_of_enemys[2];
}
//================================================================================
//this function return how many precent to continue to the next level
int Level::getPrecent()
{
	return m_percent;
}
//================================================================================
//this function return which level we are
int Level::getLevel()
{
	return m_level;
}
//================================================================================
//this function set the level
void Level::setLevel()
{
	m_level++;
}
//================================================================================
//this function load new level
void Level::loadNewLevel()
{
	m_file.close();
	open_file();
	num_of_enemys.resize(0);
	insert_data();

}
//================================================================================


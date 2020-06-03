#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using std::ifstream;
class Level
{
public:
	Level(int level = 1);
	int getNumOfRegularBall();
	int getNumOfWreckingBall();
	int getNumOfHedgehog();
	int getPrecent();
	int getLevel();
	void setLevel();
	void loadNewLevel();
private:
	int m_level;
	int m_percent;
	ifstream m_file;
	std::vector<int> num_of_enemys;
	void open_file();
	void insert_data();
};


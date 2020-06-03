#pragma once
#include <vector>
#include "Media.h"
#include "EmptyCell.h"
#include "FullCell.h"
#include "Line.h"
#include "CloseCell.h"
class Board
{
public:
	Board();
	void drawGrid(sf::RenderWindow & window);
	CellMode *  getCell(sf::Vector2i index);
	void setCell(std::unique_ptr<CellMode>, sf::Vector2i index);
	void decreaseNumOfFullCell();
	void resetBoard();
	void setLineToFullCell();
	void setCloseAreaMap();
	int getCurrPercent();
private:
	std::vector<std::vector<std::unique_ptr<CellMode>>> m_board;
	int numOfFullCells;
};


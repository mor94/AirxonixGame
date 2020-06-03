#include "Board.h"


//================================================================================
//constructor
Board::Board()
	:numOfFullCells(0)
{
	m_board.resize(BOARD_SIZE);
	for (int i = 0; i < BOARD_SIZE; i++)
		m_board[i].resize(BOARD_SIZE);
	resetBoard();
}

//================================================================================
//this function draw the board
void Board::drawGrid(sf::RenderWindow & window)
{	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			m_board[i][j]->draw(window);

		}
	}
}
//===================================================================================
//this function reset the board
void Board::resetBoard()
{
	numOfFullCells = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i == 0 || i == BOARD_SIZE - 1 || j == 0 || j == BOARD_SIZE - 1)
				m_board[i][j] = std::make_unique<FullCell>();
			else
				m_board[i][j] = std::make_unique<EmptyCell>();
			m_board[i][j]->setObjectPositionStart({(i*PICSIZE) ,j*PICSIZE });
		}
	}
}
//===================================================================================
//this function return the value of the index in the board
CellMode *  Board::getCell(sf::Vector2i index)
{
	return m_board[(index.x)/PICSIZE][(index.y)/PICSIZE].get();
}
//===================================================================================
//this function insert a cell mode to the board
void Board::setCell(std::unique_ptr<CellMode> object, sf::Vector2i index)
{
	
	if(object!=nullptr)
		object->setObjectPosition(index);
	index.x -= SHIFT;
	index.x /= PICSIZE;
	index.y /= PICSIZE;
	m_board[index.x][index.y] = std::move(object);
}

//===================================================================================
//this function replace the line cell to full cell
void Board::setLineToFullCell()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (typeid(*m_board[i][j]) == typeid(Line))
			{
				m_board[i][j] = std::make_unique<FullCell>();
				m_board[i][j]->setObjectPositionStart({ (i*PICSIZE),j*PICSIZE });
				numOfFullCells++;
			}
		}
	}
}
//===================================================================================
//this functiom replace every empty cell to full cell when helicopter close area
void Board::setCloseAreaMap()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (typeid(*m_board[i][j]) == typeid(EmptyCell))
			{
				m_board[i][j] = std::make_unique<FullCell>();
				m_board[i][j]->setObjectPositionStart({ i*PICSIZE,j*PICSIZE });
				numOfFullCells++;
			}
			else if (typeid(*m_board[i][j]) != typeid(FullCell))
			{

				m_board[i][j] = std::make_unique<EmptyCell>();
				m_board[i][j]->setObjectPositionStart({ i*PICSIZE,j*PICSIZE });
			}
		}
	}
}
//===================================================================================
//this function claculae and return the close area percent
int Board::getCurrPercent()
{
	
	return ((float)numOfFullCells /((BOARD_SIZE *BOARD_SIZE)- (BOARD_SIZE * 4))) * 100;
}
//===================================================================================
void Board::decreaseNumOfFullCell()
{
	numOfFullCells--;
}

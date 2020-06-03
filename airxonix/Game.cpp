#include "Game.h"
#include "Collision.h"
#include "TimePrize.h"
//========================================================================================
//constructor
Game::Game(sf::RenderWindow & window)
	:m_board(),m_window(window), current_percentage(0), m_heli(std::make_unique<Helicopter>()), time_of_level(60),
	frozen_prize(false),highScore(Media::instance().getFile()), poision_screen(false), runningOutTime(false)

	
{
	window.clear();

	setImages();
	createObject();

}

//===================================================================================
//This function is the main function that controll the game
bool Game::run()
{
	Media::instance().playSound(t_startSound);
	music_background.play();
	sf::Event event;
	while (m_window.isOpen())     //loop until the window is close
	{
		while (time_of_level - level_clock.getElapsedTime().asSeconds() > -1)    //play until the time of the level is over
		{
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)      //check if the user closed the window
				{
					m_window.close();
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					return true;
				}

			}

			m_window.clear();
			showImages();
			createBoard();
			createPrize();
			drawObjects();

			if (m_heli->getLife() == 0)     //check if the hekicopter is dead
			{
				
				gameOver();    //go to gameOverScreen
				return true;
			}

			if (heli_clock.getElapsedTime().asSeconds() >= heli_time.asSeconds()) //helicopter movement
			{
				moveHeli();
				heli_clock.restart();
			}

			if (poision_screen)                                                 //if helicopter in poision mode
			{
				if (prizePoision_clock.getElapsedTime().asSeconds() >= prizePoision_time.asSeconds())  //if to get out of poision mode
				{
					poision_screen = false;
				}
			}

			if (frozen_prize)                                                   //if helicopter in frozen mode
			{
				if (prizeFrozen_clock.getElapsedTime().asSeconds() >= prizeFrozen_time.asSeconds()) //if to get out of frozen mode
				{
					frozen_prize = false;
				}
			}

			if (enemy_clock.getElapsedTime().asSeconds() >= enemy_time.asSeconds() && !frozen_prize)  //enemy movement
			{
				moveBalls();
				moveHedgehog();
				enemy_clock.restart();
			}
			if (m_board.getCurrPercent() > m_level.getPrecent())    //check if the player close enough area
			{
				m_heli->setScore(100);
				newLevel();
			/*	if (m_level.getLevel() == 4)*/
					return true;
				break;
			}

			m_window.display();

		}
		gameOver();


	}

		
	
}
//========================================================================================
//This function calls to helicopters function to change helicpoters life
void Game::setHelicopterLife(int val)
{
	m_heli->setLife(val);
}
//========================================================================================
//This function reset the object and the board
void Game::reset()
{
	m_heli->reset();
	for (auto & i : m_hedgehogs)
		i->reset();

	for (int i = 1; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			auto objectCell = m_board.getCell({ i*PICSIZE,j*PICSIZE });
			if (typeid(*objectCell) == typeid(Line))
			{
				m_board.setCell(std::make_unique<EmptyCell>(), { (i*PICSIZE + SHIFT),j*PICSIZE });
			}
		}
	}
	
}
//========================================================================================
//This function create a new level
void Game::newLevel()
{
	m_level.setLevel();
	if (m_level.getLevel() == 4)
	{
		youWin();
	}
	else
	{
		m_window.clear();
		m_window.display();
		m_level.loadNewLevel();
		m_balls.resize(0);
		m_hedgehogs.resize(0);
		m_board.resetBoard();
		current_percentage = 0;
		m_heli->setHelicopterPosition();
		time_of_level = 60;
		setImages();
		createObject();
		level_clock.restart();
		levelUpScreen();
	}
}
//===================================================================================
//This function display level up screen
void Game::levelUpScreen()
{
	sf::Event event;
	m_window.draw(sprite_levelUpScreen);
	m_window.display();
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

	run();
}
//===================================================================================
//this function create the board
void Game::createBoard()
{
	m_board.drawGrid(m_window);
}
//===================================================================================
//this function create the enemies object. find how many object to create and call to
//sub function that create the objects
void Game::createObject()
{
	useFactory(t_regularBall, m_level.getNumOfRegularBall());
	useFactory(t_wreckingBall, m_level.getNumOfWreckingBall());
	useFactory(t_hedgehog, m_level.getNumOfHedgehog());
}
//===================================================================================
//this function gets type of object and amount to create and creates the objects by 
//using factoy
void Game::useFactory(myEnum type, int num)
{
	if (type == t_hedgehog)
	{
		for (int i = 0; i <num; i++)
			m_hedgehogs.emplace_back(std::move(MyFactory::create(type)));
	}
	else
	{
		for (int i = 0; i < num; i++)
			m_balls.emplace_back(std::move(MyFactory::create(type)));
	}
}
//===================================================================================
//this function draw the object.
void Game::drawObjects()
{	
	unsigned int i;
	for (const auto & i : m_balls)
		i->draw(m_window);
	for (const auto & i : m_hedgehogs)
		i->draw(m_window);
	for (const auto & i : m_prizes)
		i->draw(m_window);
	if (poision_screen)
		m_window.draw(sprite_poisionScreen);        //draw poision screen on the window
	m_heli->draw(m_window);

}
//===================================================================================
//This function control helicopter movement
void Game::moveHeli()
{
	sf::Vector2i new_pos;
	new_pos = findIndexByKey();         //find the next cell by key press

	if (m_heli->getEmptyArea())
		new_pos = findIndexbyDir(new_pos);  //if the player on empty area

	collisionMove(new_pos);
	
}
//================================================================================
//this function find the next cell of helicopter ocording to key press
sf::Vector2i Game::findIndexByKey()
{
	sf::Vector2i new_pos;
	new_pos.x = (m_heli->getSprite().getPosition().x);
	new_pos.y = (m_heli->getSprite().getPosition().y);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!m_heli->getEmptyArea())
		{
			m_heli->setDir(t_left);
			new_pos.x -= PICSIZE;
		}
		else
		{
			if (m_heli->getDir() != t_right)
			{
				m_heli->setDir(t_left);
				new_pos.x -= PICSIZE;
			}
		}
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!m_heli->getEmptyArea())
		{
			m_heli->setDir(t_right);
			new_pos.x += PICSIZE;
		}
		else
		{
			if (m_heli->getDir() != t_left)
			{
				m_heli->setDir(t_right);
				new_pos.x += PICSIZE;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!m_heli->getEmptyArea())
		{
			m_heli->setDir(t_down);
			new_pos.y += PICSIZE;
		}
		else
		{
			if (m_heli->getDir() != t_up)
			{
				m_heli->setDir(t_down);
				new_pos.y += PICSIZE;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!m_heli->getEmptyArea())
		{
			m_heli->setDir(t_up);
			new_pos.y -= PICSIZE;
		}
		else
		{
			if (m_heli->getDir() != t_down)
			{
				m_heli->setDir(t_up);
				new_pos.y -= PICSIZE;
			}
		}
	}
	return new_pos;
	
}
//================================================================================
//this function find the next cell of helicopter ocording to direction
sf::Vector2i Game::findIndexbyDir(sf::Vector2i new_pos)
{
	sound_line.play();

	if (m_heli->getSprite().getPosition() == (sf::Vector2f)new_pos)
	{
		if (m_heli->getDir() == t_down)
		{
			new_pos.y += PICSIZE;
		}
		else if (m_heli->getDir() == t_left)
		{
			new_pos.x -= PICSIZE;
		}
		else if (m_heli->getDir() == t_right)
		{
			m_heli->setDir(t_right);
			new_pos.x += PICSIZE;
		}
		else if (m_heli->getDir() == t_up)
		{
			m_heli->setDir(t_up);
			new_pos.y -= PICSIZE;
		}
		
	}
	return new_pos;	
}
//===================================================================================
//this function received a position by pixels  and check the helicopter collision
void Game::collisionMove(sf::Vector2i new_pos)
{
		if (checkLimits(new_pos))
		{
			sf::Vector2f HeliCurrnetPosition = m_heli->getSprite().getPosition();
			auto objectCell = m_board.getCell({ new_pos.x - SHIFT,new_pos.y });

			processCollision(*m_heli.get(), *objectCell, *this);
			
			if (m_heli->getCloseArea() && m_heli->getEmptyArea())   //check if helicopter pess from empty area to full area
			{
				int temp = m_board.getCurrPercent();
				closeArea();
				m_heli->setScore ( (m_board.getCurrPercent() - temp)*2);
			}
		}
		for (int i = 0; i < m_prizes.size(); i++)          //check collision with prizes
		{
			sf::Vector2i index_prize = { (int)((m_prizes[i]->getSprite().getPosition().x ) / PICSIZE) ,(int)((m_prizes[i]->getSprite().getPosition().y) / PICSIZE) };
			if (index_prize.x == (new_pos.x) / PICSIZE && index_prize.y == new_pos.y / PICSIZE)
			{
				//m_prizes[i]->playSound();
				processCollision(*m_heli.get(), *(m_prizes[i].get()), *this);
				
				m_prizes.erase(m_prizes.begin()+i);   //erase the prize from the vector
			}

		}
	
}
//===================================================================================
//This function recives an cell mode and pos and insert the cell to the board in this pos
void  Game::setBoard(std::unique_ptr<CellMode> new_object, sf::Vector2i new_pos)
{
	m_board.setCell(std::move(new_object), new_pos);
}
//===================================================================================
//this function check the limits of the board
bool Game::checkLimits(sf::Vector2i position)
{
	if (position.x >= SHIFT && position.x <= BOARD_SIZE * PICSIZE - 1 +SHIFT && position.y >= 0 && position.y <= BOARD_SIZE * PICSIZE - 1)
		return true;
	return false;
}
//===================================================================================
//this function control the balls movement
void Game::moveBalls()
{
	for (const auto & i : m_balls)
	{
		sf::Vector2i new_pos;
		new_pos.x = i->getSprite().getPosition().x + i->getAngle().x;
		new_pos.y = i->getSprite().getPosition().y + i->getAngle().y;
		auto objectCell = m_board.getCell({ new_pos.x - SHIFT,new_pos.y });
		processCollision(*i, *objectCell, *this);
	}
}
//===================================================================================
//this function delete full cell from the board
void Game::eatWall(sf::Vector2i index)
{
	setBoard(std::make_unique<EmptyCell>(), index);
	m_board.decreaseNumOfFullCell();
}
//===================================================================================
//this function control the hedgehog movement
void Game::moveHedgehog()
{
	for (const auto & i : m_hedgehogs)
	{
		sf::Vector2i new_pos;
		new_pos.x = (i->getSprite().getPosition().x);
		new_pos.y = (i->getSprite().getPosition().y);
		if (i->getDir() == 1)
			new_pos.y += PICSIZE;
		else if (i->getDir() == 2)
			new_pos.y -= PICSIZE;
		else if (i->getDir() == 3)
			new_pos.x += PICSIZE;
		else
			new_pos.x -= PICSIZE;
		if (checkLimits(new_pos))
		{
			auto objectCell = m_board.getCell({ new_pos.x - SHIFT,new_pos.y });
			processCollision(*i.get(), *objectCell, *this);
			if (i->getSprite().getGlobalBounds().intersects(m_heli->getSprite().getGlobalBounds()))
			{
				processCollision(*i.get(), *m_heli.get(), *this);
			}
		}
		else
			i->changeDir();

	}
}
//===================================================================================
//this function calls when helicopter moved to close area. the function close the appropriate cell
void Game::closeArea()
{
	m_board.setLineToFullCell();

	for (unsigned int i = 0; i<m_balls.size(); i++)
	{
		sf::Vector2i pos = (sf::Vector2i)m_balls[i]->getSprite().getPosition();
			drop({ pos.x - SHIFT, pos.y });
	}
	Media::instance().playSound(t_closeAreaSound);

	m_board.setCloseAreaMap();
	m_heli->setCloseArea(false);
	m_heli->setEmptyArea(false);
}
//===================================================================================
//this function is a recursive function .The function fills the cells that are in the area of balls in a closecell
void Game::drop(sf::Vector2i enemy_pos)
{
	if (typeid(*m_board.getCell(enemy_pos)) == typeid(EmptyCell))
		m_board.setCell(std::make_unique<CloseCell>(), { enemy_pos.x + SHIFT,enemy_pos.y });
	if (typeid(*m_board.getCell({ enemy_pos.x,enemy_pos.y - PICSIZE })) == typeid(EmptyCell))
		drop({ enemy_pos.x,enemy_pos.y - PICSIZE });
	if ( typeid(*m_board.getCell({ enemy_pos.x,enemy_pos.y + PICSIZE })) == typeid(EmptyCell))
		drop({ enemy_pos.x,enemy_pos.y + PICSIZE });
	if ( typeid(*m_board.getCell({ enemy_pos.x-PICSIZE,enemy_pos.y})) == typeid(EmptyCell))
		drop({ enemy_pos.x - PICSIZE,enemy_pos.y });
	if ( typeid(*m_board.getCell({ enemy_pos.x+PICSIZE,enemy_pos.y})) == typeid(EmptyCell))
		drop({ enemy_pos.x + PICSIZE,enemy_pos.y });

}
//===================================================================================
//this function create prizes by lottery number
void Game::createPrize()
{
	int num = rand() % CREATE_PRIZE;
	if (num == 2 || num==4)
	{
		int type =((rand() % NUM_OF_PRIZES) + 4);
		m_prizes.emplace_back(std::move(PrizeFactory::create((myEnum)type)));
		
	}
	for (int i = 0; i < m_prizes.size(); i++)
	{
		if (m_prizes[i]->getClock().getElapsedTime().asSeconds() >= m_prizes[i]->getTime().asSeconds())
		{
			m_prizes.erase(m_prizes.begin());
		}
	}
	

}
//===================================================================================
//this function display a game over screen
void Game::gameOver()
{
	sf::Event e;
	Media::instance().playSound(t_gameOverSound);
	sf::String s;
	sf::Text text(s, Media::instance().get_font(), 50);
	sf::Sprite gameOverTexture;
	gameOverTexture.setTexture(Media::instance().getTexture(t_gameOverBackground));
	sf::Text yourName("enter your name : ", Media::instance().get_font(), 50);
	sf::Text yourScore("your score : " + std::to_string(m_heli->getScore()), Media::instance().get_font(), 50);
	yourName.setOutlineThickness(2);
	yourName.setOutlineColor(sf::Color::Black);
	yourScore.setOutlineThickness(2);
	yourScore.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	yourScore.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 200 ,(BOARD_SIZE*PICSIZE) / 2 + 50 });
	text.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 570 ,(BOARD_SIZE*PICSIZE) / 2 + SHIFT / 2 });
	yourName.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 200 ,(BOARD_SIZE*PICSIZE) / 2 + SHIFT / 2 });
	while (m_window.isOpen())
	{
		m_window.clear();
		while (m_window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::TextEntered:
				if (e.key.code == 8 && s.getSize() > 0)
				{
					s.erase(s.getSize() - 1, s.getSize());
				}
				else if (s.getSize() <= 20)
					s += (char)e.text.unicode;
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Return)
				{
					if (Media::instance().getHighScore().size()< 5)
						insertToMap(m_heli->getScore(), s);	
					return;
				}
				
				break;
			}
		}
		text.setString(s);
		m_window.draw(gameOverTexture);
		m_window.draw(text);
		m_window.draw(yourScore);
		m_window.draw(yourName);
		m_window.display();
	}
}
//===================================================================================
//this function update frozen_prize value
void Game::setFrozenPrize(bool value)
{
	frozen_prize=value;
}
//===================================================================================
//this function return frozen_prize value
bool Game::getFrozenPrize()
{
	return frozen_prize;
}
//===================================================================================
//this function update poision screen value
void Game::setPoisionScreen(bool value)
{
	poision_screen = value;
}
//===================================================================================
//this function calls from the collision between helicopther to prize
void Game::restartFrozenPrizeClock()
{
	prizeFrozen_clock.restart();
}
//===================================================================================
//this function restart the poision prize clock
void Game::restartPoisionPrizeClock()
{
	prizePoision_clock.restart();
}
//===================================================================================
//this function update the high scores map
void Game::insertToMap(unsigned int score, std::string name)
{

	std::multimap<unsigned int, std::string> & high_score = Media::instance().getHighScore();
	high_score.emplace(score, name);

}
//===================================================================================
//this function close the high score file
void Game::closeFile()
{
	highScore.close();
}
//===================================================================================
//this function update the time of the level
void Game::setTimeOfLevel(int seconds)
{
	time_of_level += seconds;
}
//===================================================================================
//this function display the images on the screen
void Game::showImages()
{
	m_window.draw(sprite_background);
	m_window.draw(sprite_board);
	m_window.draw(sprite_heart);
	m_window.draw(sprite_clock);
	life_text.setString(std::to_string(m_heli->getLife()));
	m_window.draw(life_text);
	m_window.draw(level_text);
	percent_text.setString(std::to_string(m_board.getCurrPercent()) + "% of " + std::to_string(m_level.getPrecent()) + "%");
	m_window.draw(percent_text);
	score_text.setString("Score : " + std::to_string(m_heli->getScore()));
	m_window.draw(score_text);

	clock_text.setString(std::to_string((int)time_of_level - (int)level_clock.getElapsedTime().asSeconds()));
	m_window.draw(clock_text);
	

}
//===================================================================================
//this function restart the images
void Game::setImages()
{
	life_text.setFont(Media::instance().get_font());
	life_text.setString(std::to_string(m_heli->getLife()));
	life_text.setPosition({ 20,3 });

	level_text.setFont(Media::instance().get_font());
	level_text.setString("Level : " + std::to_string(m_level.getLevel()));
	level_text.setPosition({ 20,600 });

	percent_text.setFont(Media::instance().get_font());
	percent_text.setString(std::to_string(m_board.getCurrPercent()) + "%" + "of " + std::to_string(m_level.getPrecent()) + "%");
	percent_text.setPosition({ 1000,550 });

	clock_text.setFont(Media::instance().get_font());
	clock_text.setString(std::to_string((int)time_of_level - (int)level_clock.getElapsedTime().asSeconds()));
	clock_text.setPosition({ 970,17 });

	score_text.setFont(Media::instance().get_font());
	score_text.setString("Score : " + std::to_string(m_heli->getScore()));
	score_text.setPosition({ 1000, 600 });

	sprite_background.setTexture(Media::instance().getTexture(t_background));
	sprite_board.setTexture(Media::instance().getTexture(t_board));
	sprite_board.setPosition({ SHIFT,0 });
	sprite_heart.setTexture(Media::instance().getTexture(t_heart));
	sprite_heart.setPosition({ 30,0 });
	sprite_clock.setTexture(Media::instance().getTexture(t_clock));
	sprite_clock.setPosition({950,3});

	sprite_levelUpScreen.setTexture(Media::instance().getTexture(t_levelUpScreen));
	sprite_poisionScreen.setTexture(Media::instance().getTexture(t_poisionScreen));
	sprite_poisionScreen.setPosition({ SHIFT,0 });
	
	music_background.openFromFile("BackgroundSound.ogg");
	music_background.setLoop(true);
	music_background.setVolume(5);

	
}
//=================================================================================
void Game::youWin()
{
	sf::Event e;
	sf::String s;
	sf::Text text(s, Media::instance().get_font(), 50);
	sf::Sprite gameOverTexture;
	gameOverTexture.setTexture(Media::instance().getTexture(t_youWinBackground));
	sf::Text yourName("enter your name : ", Media::instance().get_font(), 50);
	sf::Text yourScore("your score : " + std::to_string(m_heli->getScore()), Media::instance().get_font(), 50);
	yourName.setOutlineThickness(2);
	yourName.setOutlineColor(sf::Color::Black);
	yourScore.setOutlineThickness(2);
	yourScore.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	yourScore.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 200 ,(BOARD_SIZE*PICSIZE) / 2 + 50 });
	text.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 570 ,(BOARD_SIZE*PICSIZE) / 2 + SHIFT / 2 });
	yourName.setPosition({ (BOARD_SIZE*PICSIZE) / 3 + 200 ,(BOARD_SIZE*PICSIZE) / 2 + SHIFT / 2 });
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::TextEntered:
				if (e.key.code == 8 && s.getSize() > 0)
				{
					s.erase(s.getSize() - 1, s.getSize());
				}
				else if (s.getSize() <= 20)
					s += (char)e.text.unicode;
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Return)
				{
					if (Media::instance().getHighScore().size() < 5)
						insertToMap(m_heli->getScore(), s);
					return;
				}

				break;
			}
			text.setString(s);
			m_window.clear();
			m_window.draw(gameOverTexture);
			m_window.draw(text);
			m_window.draw(yourScore);
			m_window.draw(yourName);
			m_window.display();

		}
	}
}
#include "Collision.h"
#include <map>
#include <string>
#include <typeindex>
#include "EmptyCell.h"
#include "FullCell.h"
#include "Hedgehog.h"
#include "Line.h"
#include "RegularBall.h"
#include "WreckingBall.h"
#include "BoostPrize.h"
#include "TimePrize.h"
#include "LifePrize.h"
#include "PoisonPrize.h"
#include "CoinPrize.h"

namespace { // unnamed namespace — the standard way to make function "static"

			// primary collision-processing functions
	//============================================================================== helicopter
	void helicopterFullCell(Object& helicopter,
		Object& fullCell, Game & g)
	{
		Helicopter & h = static_cast<Helicopter &>(helicopter);
		h.move((sf::Vector2i)fullCell.getSprite().getPosition());
		h.setCloseArea(true);
	}

	//==============================================================================
	void helicopterEmptyCell(Object& helicopter,
		Object& emptyCell, Game & g)
	{
		//Media::instance().playSound(t_lineSound);

		Helicopter & h = static_cast<Helicopter &>(helicopter);
		h.setEmptyArea(true);
		h.setCloseArea(false);
		h.move((sf::Vector2i)emptyCell.getSprite().getPosition());
		g.setBoard(std::make_unique<Line>(), (sf::Vector2i)emptyCell.getSprite().getPosition());

	}

	//==============================================================================
	void helicopterLine(Object& helicopter,
		Object& line, Game & g)
	{
		Media::instance().playSound(t_OoSound);
		g.setHelicopterLife(-1);
		g.reset();
	}

	//==============================================================================
	void helicopterRegularBall(Object& helicopter,
		Object& regularBall, Game & g)
	{
		helicopterLine(helicopter, regularBall, g);
	}
	//==============================================================================
	void helicopterWreckingBall(Object& helicopter,
		Object& wreckingBall, Game & g)
	{
	}
	//==============================================================================
	void helicopterHedgehog(Object& helicopter,
		Object& hedgehog, Game & g)
	{
		helicopterLine(helicopter, hedgehog, g);
	}
	//==============================================================================
	//זה לא מהירות זה הקפאת השחקנים, צריך לשנות שם
	void helicopterBoostPrize(Object& helicopter,
		Object& boostPrize, Game & g)
	{
		Media::instance().playSound(t_frozenPrizeSound);
		g.setFrozenPrize(true);            //change the boll var to true;
		g.restartFrozenPrizeClock();
	}
	//==============================================================================
	void helicopterLifePrize(Object& helicopter,
		Object& lifePrize, Game & g)
	{
		Helicopter & h = static_cast<Helicopter &>(helicopter);
		Media::instance().playSound(t_lifePrizeSound);
		g.setHelicopterLife(+1);

	}
	//==============================================================================
	void helicopterPoisionPrize(Object& helicopter,
		Object& poisionPrize, Game & g)
	{
		Media::instance().playSound(t_poisionPrizeSound);
		g.setPoisionScreen(true);
		g.restartPoisionPrizeClock();
	}
	//==============================================================================
	void helicopterTimePrize(Object& helicopter,
		Object& timePrize, Game & g)
	{
		Media::instance().playSound(t_timePrizeSound);
		g.setTimeOfLevel(5);
	}
	//==============================================================================
	void helicopterCoinPrize(Object& helicopter,
		Object& coinPrize, Game & g)
	{
		Helicopter & h = static_cast<Helicopter &>(helicopter);
		Media::instance().playSound(t_scorePrizeSound);

		h.setScore(10);
	}
	//==============================================================================hedghog
	void hedgehogHelicopter(Object& hedgehog,
		Object & helicopter, Game & g)
	{
		helicopterLine(helicopter, hedgehog, g);
	}
	//==============================================================================
	void hedgehogFullCell(Object& hedgehog,
		Object& fullCell, Game & g)
	{
		Hedgehog & h = static_cast<Hedgehog &>(hedgehog);
		h.move((sf::Vector2i)fullCell.getSprite().getPosition());
	}
	//==============================================================================
	void hedgehogEmptyCell(Object& hedgehog,
		Object& emptyCell, Game & g)
	{
		Hedgehog & h = static_cast<Hedgehog &>(hedgehog);
		h.changeDir();
	}

	//==============================================================================wrecking ball
	void wreckingBallLine(Object& wreckingBall,
		Object& line, Game & g)
	{
		helicopterLine(wreckingBall, line, g);
	}
	//==============================================================================
	void wreckingBallRegularBall(Object& wreckingBall,
		Object& regularBall, Game & g)
	{

	}
	//==============================================================================
	void wreckingBallEmptyCell(Object& wreckingBall,
		Object& emptyCell, Game & g)
	{
		WreckingBall & w = static_cast<WreckingBall &>(wreckingBall);
		w.move((sf::Vector2i)emptyCell.getSprite().getPosition());
	}

	//==============================================================================
	void wreckingBallWreckingBall(Object& wreckingBall1,
		Object& wreckingBall2, Game & g)
	{

	}
	//==============================================================================
	void wreckingBallHelicopter(Object& wreckingBall,
		Object& helicopter, Game & g)
	{
		helicopterWreckingBall(helicopter, wreckingBall, g);
	}
	//==============================================================================
	void wreckingBallFullCell(Object& wreckingBall,
		Object& fullCell, Game & g)
	{

		WreckingBall & w = static_cast<WreckingBall &>(wreckingBall);
		sf::Vector2i position = (sf::Vector2i)fullCell.getSprite().getPosition();
		if (position.x > SHIFT && position.x < BOARD_SIZE * PICSIZE + SHIFT - PICSIZE && position.y >0 && position.y < BOARD_SIZE * PICSIZE - PICSIZE)
		{
			g.eatWall(position);
		}
			
		w.setIncline();
	}

	//==============================================================================full cell
	void fullCellHelicopter(Object&  fullCell,
		Object& helicopter, Game & g)
	{
		helicopterFullCell(helicopter, fullCell, g);

	}
	//==============================================================================
	void fullCellWreckingBall(Object& fullCell ,
		Object& wreckingBall, Game & g)
	{
		wreckingBallFullCell(wreckingBall, fullCell, g);
	}
	//==============================================================================*************************
	void regularBallFullCell(Object& regularBall,
		Object& fullCell, Game & g)
	{

		RegularBall & r = static_cast<RegularBall &>(regularBall);
		r.setIncline();
	}
	//==============================================================================
	void fullCellregularBall(Object& fullCell ,
		Object& regularBall, Game & g)
	{
		regularBallFullCell(regularBall, fullCell, g);
	}

	//==============================================================================
	void lineWreckingBall(Object& line,
		Object& wreckingBall, Game & g)
	{
		wreckingBallLine(wreckingBall, line, g);
	}
	//==============================================================================
	void lineRegularBall(Object& line,
		Object& regularBall , Game & g)
	{
		helicopterLine(regularBall, regularBall, g);
	}
	//==============================================================================empty cell

	void EmptyCellHelicopter(Object&emptyCell,
		Object& helicopter, Game & g)
	{
		helicopterEmptyCell(helicopter, emptyCell, g);
	}
	//==============================================================================
	void emptyCellWreckingBall(Object& wreckingBall,
		Object& emptyCell, Game & g)
	{
		wreckingBallEmptyCell(wreckingBall, emptyCell, g);
	}
	//==============================================================================
	void regularBallHelicopter(Object& regularBall,
		Object& helicopter, Game & g)
	{

		helicopterLine(helicopter, regularBall, g);

	}
	//==============================================================================
	void regularBallEmptyCell(Object& regularBall,
		Object& emptyCell, Game & g)
	{
		RegularBall & r = static_cast<RegularBall &>(regularBall);
		r.move((sf::Vector2i)emptyCell.getSprite().getPosition());
	}
	//==============================================================================
	void regularBallLine(Object& regularBall,
		Object& line, Game & g)
	{
		helicopterLine(regularBall, regularBall, g);

	}
	
	//==============================================================================

	
	using HitFunctionPtr = void(*)(Object &, Object & ,Game & g);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Helicopter), typeid(FullCell))] = &helicopterFullCell;
		phm[Key(typeid(Helicopter), typeid(Hedgehog))] = &helicopterHedgehog;
		phm[Key(typeid(Helicopter), typeid(EmptyCell))] = &helicopterEmptyCell;
		phm[Key(typeid(Helicopter), typeid(RegularBall))] = &helicopterRegularBall;
		phm[Key(typeid(Helicopter), typeid(WreckingBall))] = &helicopterWreckingBall;
		phm[Key(typeid(Helicopter), typeid(Line))] = &helicopterLine;
		phm[Key(typeid(Helicopter), typeid(BoostPrize))] = &helicopterBoostPrize;
		phm[Key(typeid(Helicopter), typeid(LifePrize))] = &helicopterLifePrize;
		phm[Key(typeid(Helicopter), typeid(TimePrize))] = &helicopterTimePrize;
		phm[Key(typeid(Helicopter), typeid(CoinPrize))] = &helicopterCoinPrize;
		phm[Key(typeid(Helicopter), typeid(PoisonPrize))] = &helicopterPoisionPrize;


		phm[Key(typeid(FullCell), typeid(Helicopter))] = &fullCellHelicopter;
		phm[Key(typeid(FullCell), typeid(WreckingBall))] = &fullCellWreckingBall;
		phm[Key(typeid(FullCell), typeid(RegularBall))] = &fullCellregularBall;


		phm[Key(typeid(EmptyCell), typeid(Helicopter))] = &EmptyCellHelicopter;
		phm[Key(typeid(EmptyCell), typeid(WreckingBall))] = &wreckingBallEmptyCell;


		phm[Key(typeid(Hedgehog), typeid(Helicopter))] = &hedgehogHelicopter;
		phm[Key(typeid(Hedgehog), typeid(FullCell))] = &hedgehogFullCell;
		phm[Key(typeid(Hedgehog), typeid(EmptyCell))] = &hedgehogEmptyCell;

		phm[Key(typeid(RegularBall), typeid(Helicopter))] = &regularBallHelicopter;
		phm[Key(typeid(RegularBall), typeid(Line))] = &regularBallLine;

		phm[Key(typeid(RegularBall), typeid(FullCell))] = &regularBallFullCell;
		phm[Key(typeid(RegularBall), typeid(EmptyCell))] = &regularBallEmptyCell;

		phm[Key(typeid(WreckingBall), typeid(Helicopter))] = &wreckingBallHelicopter;
		phm[Key(typeid(WreckingBall), typeid(RegularBall))] = &wreckingBallRegularBall;
		phm[Key(typeid(WreckingBall), typeid(WreckingBall))] = &wreckingBallWreckingBall;
		phm[Key(typeid(WreckingBall), typeid(Line))] = &wreckingBallLine;
		phm[Key(typeid(WreckingBall), typeid(FullCell))] = &wreckingBallFullCell;
		phm[Key(typeid(WreckingBall), typeid(EmptyCell))] = &wreckingBallEmptyCell;

		phm[Key(typeid(Line), typeid(WreckingBall))] = &lineWreckingBall;
		phm[Key(typeid(Line), typeid(RegularBall))] = &lineRegularBall;



			
		return phm;

	}
	//==============================================================================
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
		{
			static HitMap collisionMap = initializeCollisionMap();
			auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
			if (mapEntry == collisionMap.end())
			{
				return nullptr;
			}
			return mapEntry->second;
		}
	}
 // end namespace
 //==============================================================================
void processCollision(Object & object1, Object & object2,Game & g)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2,g);
}


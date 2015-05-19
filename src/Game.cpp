/*--------------------------------------------------------------------------*/
#include <boost/numeric/conversion/converter.hpp>
/*--------------------------------------------------------------------------*/
#include "Cell.h"
#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "Route.h"
#include "ScoreTable.h"
#include "Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Game::Game(pGrid grid_, pPlayer playerLeft_, pPlayer playerRight_, bool ftr, pScoreTable scoreTable) : _firstTurnRight(ftr), _grid(grid_), _playerLeft(playerLeft_), _playerRight(playerRight_), _scoreTable(scoreTable)
{

}

/***********************************************/
Game::~Game()
{

}

/***********************************************/
pGrid Game::grid() const
{
	return _grid;
}

/***********************************************/
void Game::move(pRoute route)
{
	if(route->unit()->owner() != _currPlayer)
		THROW("Player's trying to move opp's unit");

	if(route->unit() != route->route().at(0)->occupier())
		THROW("Unit is not occupier");

	if(_unitsMovedThisTurn.find(route->unit()) != _unitsMovedThisTurn.end())
		THROW("Unit can't move more than once per turn")
	else
		_unitsMovedThisTurn.insert(route->unit());

	if(route->unit()->moveRange() < route->route().size() - 1) // -starting point
		THROW("Move range of unit exceeded");

	for(size_t i = 1; i < route->route().size(); ++i)
	{
		pCell dest = route->route().at(i);
		pCell src = route->route().at(i - 1);

		if(!dest->occupiable())
			THROW("Cell isn't occupiable");

		if(dest->occupier())
		{
			if(dest->occupier()->owner() == route->unit()->owner())
				THROW("Cell is occupied by friendly unit")
			else
				attack(src, dest);
		}
		else if(Grid::adjacency(src, dest))
		{
			 dest->occupy(src->occupier());
			 src->free();
		}
		else
			THROW("Come on, cells are not even adjacent");
	}

}

/***********************************************/
pPlayer Game::playerLeft() const
{
	return _playerLeft;
}

/***********************************************/
pPlayer Game::playerRight() const
{
	return _playerRight;
}

/***********************************************/
pScoreTable Game::scoreTable() const
{
	return _scoreTable;
}

/***********************************************/
void Game::run()
{
	if(!grid() || !playerLeft() || !playerRight())
		THROW("Grid or players are not set");

	grid()->setState(GridState::Initial);
	grid()->setState(GridState::LeftPlayerPlacing);
	playerLeft()->initGrid(shared_from_this(), Side::Left);
	grid()->setState(GridState::RightPlayerPlacing);
	playerLeft()->initGrid(shared_from_this(), Side::Right);

	while(!isOver())
	{
		grid()->setState(GridState::Turn, nextPlayer());
		_currPlayer->turn(shared_from_this());
		_unitsMovedThisTurn.clear();
	}

	grid()->setState(GridState::Initial);
}

/***********************************************/
void Game::attack(pCell src, pCell dest)
{
	pUnit attacker = src->occupier();
	pUnit victim = src->occupier();
	bool retaliation = attacker->attackRange() == 1;
	AttackInt damage = calcDamage(attacker, victim);

	if(Grid::distance(src, dest) > attacker->attackRange())
		THROW("Attack range exceeded");



}

/***********************************************/
AttackInt Game::calcDamage(pUnit attacker, pUnit victim)
{
	ModifierFloat healthRel = attacker->health() / attacker->baseHealth();
	ModifierFloat healthMod = 2 * healthRel + 0.5; // y = 2x + 0.5;

	return std::ceil(attacker->attack() * attacker->attackModifier(victim->type()) * healthMod);
}

/***********************************************/
pPlayer Game::nextPlayer() const
{
	if(!_currPlayer)
		_currPlayer = _firstTurnRight ? playerRight() : playerLeft();
	else
		_currPlayer = _currPlayer == playerLeft() ? playerRight() : playerLeft();

	return _currPlayer;
}

/***********************************************/
bool Game::isOver()
{
	size_t plUnitsAlive = 0;
	size_t prUnitsAlive = 0;

	for(CellInt col = 0; col < grid()->colNum(); ++col)
	{
		for(CellInt row = 0; row < grid()->rowNum(); ++row)
		{
			pCell cell = grid()->at(col, row);
			pUnit unit = cell->occupier();

			if(unit)
			{
				if(unit->owner() == playerLeft())
					++plUnitsAlive;
				else if(unit->owner() == playerRight())
					++prUnitsAlive;
				else
					qWarning() << "Unknown owner";
			}
		}
	}
	
	if(plUnitsAlive == 0 && prUnitsAlive == 0)
	{
		scoreTable()->addScore(playerLeft(), ScoreEnum::Tie);
		scoreTable()->addScore(playerRight(), ScoreEnum::Tie);
		
		return true;
	}
	else if(plUnitsAlive == 0 && prUnitsAlive > 0)
	{
		scoreTable()->addScore(playerLeft(), ScoreEnum::Lose);
		scoreTable()->addScore(playerRight(), ScoreEnum::Win);

		return true;
	}
	else if(plUnitsAlive > 0 && prUnitsAlive == 0)
	{
		scoreTable()->addScore(playerLeft(), ScoreEnum::Win);
		scoreTable()->addScore(playerRight(), ScoreEnum::Lose);

		return true;
	}
	else if(plUnitsAlive > 0 && prUnitsAlive > 0)
	{
		return false;
	}
	else
	{
		qWarning() << "Err while calc result";

		return true;
	}
}

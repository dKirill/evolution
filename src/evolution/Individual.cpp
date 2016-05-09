/*--------------------------------------------------------------------------*/
#include "evolution/Individual.h"
#include "game/Cell.h"
#include "game/Game.h"
#include "game/Grid.h"
#include "game/Route.h"
#include "game/Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Individual::Individual(RandEngine& reng)
{
	init(_attackPriorities[UnitType::Archer], reng);
	init(_attackPriorities[UnitType::Horseman], reng);
	init(_attackPriorities[UnitType::Pikeman], reng);
	init(_attackPriorities[UnitType::Swordsman], reng);
}

/***********************************************/
Individual::~Individual()
{

}

/***********************************************/
GeneInt toGeneInt(const UnitType utype)
{
	return static_cast<GeneInt>(utype);
}

/***********************************************/
UnitType toUnitType(const GeneInt gint)
{
	if(toGeneInt(UnitType::Archer) == gint)
		return UnitType::Archer;
	else if(toGeneInt(UnitType::Horseman) == gint)
		return UnitType::Horseman;
	else if(toGeneInt(UnitType::Pikeman) == gint)
		return UnitType::Pikeman;
	else if(toGeneInt(UnitType::Swordsman) == gint)
		return UnitType::Swordsman;

	THROW("Bad gint");
}

/***********************************************/
void Individual::initGrid(pGame game, Side side)
{
	std::vector<std::tuple<CellInt, CellInt, pCell>> startingAreaPrototype; //0 - column, 1 - row
	CellType typeToFind = side == Side::Left ? CellType::LeftStartingArea : CellType::RightStartingArea;
	CellInt lowestColumn = std::numeric_limits<CellInt>::max();
	CellInt lowestRow = std::numeric_limits<CellInt>::max();
	decltype(_startingPositions)::const_iterator stpciter;

	for(CellInt row = 0; row < game->grid()->rowNum(); ++row)
	{
		std::vector<std::tuple<CellInt, CellInt, pCell>> temp;

		for(CellInt column = 0; column < game->grid()->colNum(); ++column)
		{
			if(game->grid()->at(column, row)->cellType() == typeToFind)
			{
				lowestColumn = std::min(column, lowestColumn);
				lowestRow = std::min(row, lowestRow);
				temp.push_back(std::make_tuple(column, row, game->grid()->at(column, row)));
			}
		}

		if(side == Side::Right) //mirror
		{
			for(CellInt i = 0, j = temp.size() - 1; i < j; ++i, --j)
				std::swap(temp.at(i), temp.at(j));
		}

		startingAreaPrototype.insert(startingAreaPrototype.end(), temp.begin(), temp.end());
	}

	if(std::min(lowestColumn, lowestRow) > 0)
	{
		for(auto& tupref : startingAreaPrototype)
		{
			std::get<0>(tupref) -= lowestColumn;
			std::get<1>(tupref) -= lowestRow;
		}
	}

	if(_startingPositions.size() == 0) //not initialized
	{
		std::uniform_int_distribution<GeneInt> uiDist;

		uiDist.param(std::uniform_int_distribution<GeneInt>::param_type(toGeneInt(UnitType::Archer), toGeneInt(UnitType::Swordsman)));

		for(auto const& gridref : startingAreaPrototype)
			_startingPositions.push_back(std::make_tuple(std::get<0>(gridref), std::get<1>(gridref), Gene(1, toGeneInt(UnitType::Archer), toGeneInt(UnitType::Swordsman), uiDist(game->randEngine()))));
	}
	else
	{
		if(startingAreaPrototype.size() != _startingPositions.size())
			THROW("Grid isn't compatible 1");

		if(std::equal(startingAreaPrototype.begin(), startingAreaPrototype.end(), _startingPositions.begin(), [](decltype(*std::begin(startingAreaPrototype)) sapref, decltype(*std::begin(_startingPositions)) spref) { return (std::get<0>(sapref) == std::get<0>(spref)) && (std::get<1>(sapref) == std::get<1>(spref)); }))
			THROW("Grid isn't compatible 2");
	}

	stpciter = _startingPositions.begin();

	for(auto& sapref : startingAreaPrototype)
	{
		if(stpciter == _startingPositions.end())
			THROW("Grid init logic err");

		game->place(std::get<2>(sapref), pUnit(new Unit(shared_from_this(), toUnitType(std::get<2>(*stpciter).value()))));
	}
}

/***********************************************/
void Individual::turn(pGame game)
{
	std::set<pCell> allies;
	std::set<pCell> enemies;

	//find allies & enemies
	for(CellInt row = 0; row < game->grid()->rowNum(); ++row)
	{
		for(CellInt column = 0; column < game->grid()->colNum(); ++column)
		{
			pCell cell = game->grid()->at(column, row);

			if(cell->occupier())
			{
				if(cell->occupier()->owner() == shared_from_this())
					allies.insert(cell);
				else
					enemies.insert(cell);
			}
		}
	}

	//move every ally
	for(auto const& aref : allies)
	{
		pUnit unit = aref->occupier();
		pCell dest;
		std::set<pCell, std::function<bool(pCell, pCell)>> sorted(
																[&](pCell c1, pCell c2) -> bool
																{
																	RangeInt distance1 = game->grid()->distanceAchievable(aref, c1);
																	RangeInt distance2 = game->grid()->distanceAchievable(aref, c2);
																	bool c1reachable = game->grid()->attackReachable(aref, c1);
																	bool c2reachable = game->grid()->attackReachable(aref, c2);
																	bool equalPriorities = this->_attackPriorities.at(unit->type()).at(c1->occupier()->type()).value() == this->_attackPriorities.at(unit->type()).at(c2->occupier()->type()).value();

																	//if aref can attack c1 or c2
																	if(c1reachable || c2reachable)
																	{
																		//if both within range of attack
																		if(c1reachable && c2reachable)
																		{
																			//if equal priorities, compare distance; else compare priorities
																			if(equalPriorities)
																				return distance1 < distance2;
																			else
																				return this->_attackPriorities.at(unit->type()).at(c1->occupier()->type()).value() < this->_attackPriorities.at(unit->type()).at(c2->occupier()->type()).value();
																		}
																		//else pick reachable
																		else
																			return c1reachable < c2reachable;
																	}
																	//if both r too far, compare distance and pick closest
																	else
																		return distance1 < distance2;
																});

		sorted.insert(enemies.begin(), enemies.end());
		dest = *(sorted.begin());
		game->process(game->grid()->buildRoute(aref, dest));
	}
}

/***********************************************/
void Individual::init(std::map<UnitType, Gene>& aps, RandEngine& reng)
{
	std::uniform_int_distribution<GeneInt> uiDist;

	uiDist.param(std::uniform_int_distribution<GeneInt>::param_type(toGeneInt(UnitType::Archer), toGeneInt(UnitType::Swordsman)));
	aps.insert(std::make_pair(UnitType::Archer, Gene(1, toGeneInt(UnitType::Swordsman), toGeneInt(UnitType::Archer), uiDist(reng))));
	aps.insert(std::make_pair(UnitType::Horseman, Gene(1, toGeneInt(UnitType::Swordsman), toGeneInt(UnitType::Archer), uiDist(reng))));
	aps.insert(std::make_pair(UnitType::Pikeman, Gene(1, toGeneInt(UnitType::Swordsman), toGeneInt(UnitType::Archer), uiDist(reng))));
	aps.insert(std::make_pair(UnitType::Swordsman, Gene(1, toGeneInt(UnitType::Swordsman), toGeneInt(UnitType::Archer), uiDist(reng))));
}

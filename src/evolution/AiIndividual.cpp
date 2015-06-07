/*--------------------------------------------------------------------------*/
#include "evolution/AiIndividual.h"
#include "game/Cell.h"
#include "game/Game.h"
#include "game/Grid.h"
#include "game/Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
AiIndividual::AiIndividual()
{

}

/***********************************************/
AiIndividual::~AiIndividual()
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
void AiIndividual::initGrid(pGame game, Side side, RandEngine& reng)
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
			_startingPositions.push_back(std::make_tuple(std::get<0>(gridref), std::get<1>(gridref), Gene(1, toGeneInt(UnitType::Archer), toGeneInt(UnitType::Swordsman), uiDist(reng))));
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
void AiIndividual::turn(pGame game)
{
	//TODO
}

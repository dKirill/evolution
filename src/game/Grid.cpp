/*--------------------------------------------------------------------------*/
#include <functional>
#include <sstream>
/*--------------------------------------------------------------------------*/
#include "game/Cell.h"
#include "game/Grid.h"
#include "game/Route.h"
#include "game/Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Grid::Grid(const std::string& init)
{
	UnitsInt unitsNum = 0;
	CellInt colNum = 0;
	CellInt rowNum = 0;
	std::stringstream ss(init);

	if(!(ss >> unitsNum >> colNum >> rowNum))
		THROW("Error while reading grid constants");

	if(unitsNum > colNum * rowNum / 2 || unitsNum == 0 || colNum == 0 || rowNum == 0)
		THROW("Invalid grid constants. uNum=" << unitsNum << ", cNum=" << colNum << ", rNum=" << rowNum);

	_grid.reserve(colNum);

	for(CellInt col = 0; col < colNum; ++col)
	{
		_grid.at(col).reserve(rowNum);
		std::vector<pCell>& columnVecRef = _grid.at(col);

		for(CellInt row = 0; row < rowNum; ++row)
		{
			pCell cell;
			uint8_t cellTypeInt;

			if(!(ss >> cellTypeInt))
				THROW("Error while reading grid");

			cell = pCell(new Cell(Cell::intToCellType(cellTypeInt), col, row));
			columnVecRef.push_back(cell);
		}
	}
}

/***********************************************/
Grid::~Grid()
{

}

/***********************************************/
bool Grid::adjacency(pCell c1, pCell c2)
{
	return distance(c1, c2) == 1;
}

/***********************************************/
pCell Grid::at(const CellInt col, const CellInt row) const
{
	return _grid.at(col).at(row);
}

/***********************************************/
bool Grid::attackReachable(pCell c1, pCell c2) const
{
	return distanceAchievable(c1, c2) <= c1->occupier()->moveRange() - 1 + c1->occupier()->attackRange();
}

/***********************************************/
pRoute Grid::buildRoute(pCell c1, pCell c2) const
{
	pRoute route;
	uint8_t dist = 0;
	pCell curr = c1;
	std::set<pCell> visited;
	pUnit attacker = c1->occupier();

	visited.insert(curr);

	while(curr != c2)
	{
		std::set<pCell, std::function<bool(pCell, pCell)>> availableMoves([c2](pCell lc1, pCell lc2) -> bool { return distance(lc1, c2) < distance(lc2, c2); }); // first element is closest to dest.

		//bidlokod:
		if(exists(curr->column() + 1, curr->row()) && at(curr->column() + 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() + 1, curr->row()));

		if(exists(curr->column(), curr->row() + 1) && at(curr->column(), curr->row() + 1)->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() + 1));

		if(exists(curr->column() - 1, curr->row()) && at(curr->column() - 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() - 1, curr->row()));

		if(exists(curr->column(), curr->row() - 1) && at(curr->column(), curr->row() - 1)->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() - 1));

		if(availableMoves.empty())
			THROW("Fuck your grid");

		curr = *(availableMoves.begin());
		++dist;
	}

	return dist;
}

/***********************************************/
CellInt Grid::colNum() const
{
	return _grid.size();
}

/***********************************************/
RangeInt Grid::distance(pCell c1, pCell c2)
{
	return std::abs(c1->column() - c2->column()) + std::abs(c1->row() - c2->row());
}

/***********************************************/
RangeInt Grid::distanceAchievable(pCell c1, pCell c2) const
{
	uint8_t dist = 0;
	pCell curr = c1;
	std::set<pCell> visited;

	visited.insert(curr);

	while(curr != c2)
	{
		std::set<pCell, std::function<bool(pCell, pCell)>> availableMoves([c2](pCell lc1, pCell lc2) -> bool { return distance(lc1, c2) < distance(lc2, c2); }); // first element is closest to dest.

		//bidlokod:
		if(exists(curr->column() + 1, curr->row()) && at(curr->column() + 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() + 1, curr->row()));

		if(exists(curr->column(), curr->row() + 1) && at(curr->column(), curr->row() + 1)->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() + 1));

		if(exists(curr->column() - 1, curr->row()) && at(curr->column() - 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() - 1, curr->row()));

		if(exists(curr->column(), curr->row() - 1) && at(curr->column(), curr->row() - 1)->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() - 1));

		if(availableMoves.empty())
			THROW("Fuck your grid");

		curr = *(availableMoves.begin());
		++dist;
	}

	return dist;
}

/***********************************************/
pGrid Grid::getEmptyCopy() const
{
	pGrid copy(new Grid);
	size_t col = 0;

	copy->_grid.reserve(colNum());
	copy->setState(GridState::Initial);

	for(auto const& colVecRef : _grid)
	{
		size_t row = 0;
		auto& colCopiedVecRef = copy->_grid.at(col++);

		colCopiedVecRef.reserve(rowNum());

		for(auto const& cellRef : colVecRef)
		{
			colCopiedVecRef.at(row++) = cellRef->getEmptyCopy();
		}
	}

	return copy;
}

/***********************************************/
bool Grid::exists(const CellInt col, const CellInt row) const
{
	if(col >= 0 && col < colNum() && row >= 0 && row < rowNum())
		return true;
	else
		false;
}

/***********************************************/
CellInt Grid::rowNum() const
{
	return _grid.at(0).size();
}

/***********************************************/
void Grid::setState(const GridState newstate, pPlayer permissionRecipient)
{
	_permissionOwner = permissionRecipient;

	switch(newstate)
	{
		case(GridState::Initial):
		{
			for(auto const& colVecRef : _grid) //reset of all cells
			{
				for(auto const& cellRef : colVecRef)
				{
					cellRef->free();
				}
			}

			break;
		}
		case(GridState::LeftPlayerPlacing):
		{
			if(state() != GridState::Initial)
				THROW("Impossible state change 1");

			if(!_permissionOwner)
				THROW("No _permissionOwner set");

			break;
		}
		case(GridState::RightPlayerPlacing):
		{
			if(state() != GridState::LeftPlayerPlacing)
				THROW("Impossible state change 2");

			if(!_permissionOwner)
				THROW("No _permissionOwner set");

			break;
		}
		case(GridState::Turn):
		{
			if(state() != GridState::RightPlayerPlacing || state() != GridState::Turn)
				THROW("Impossible state change 3");

			if(!_permissionOwner)
				THROW("No _permissionOwner set");

			break;
		}
	}

	_state = newstate;
}

/***********************************************/
GridState Grid::state() const
{
	return _state;
}

/***********************************************/
UnitsInt Grid::unitsPerPlayer() const
{
	return _unitsPerPlayer;
}

/***********************************************/
Grid::Grid()
{

}

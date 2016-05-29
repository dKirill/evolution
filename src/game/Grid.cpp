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

	qDebug() << init.c_str();

	if(!(ss >> unitsNum >> colNum >> rowNum))
		THROW("Error while reading grid constants");

	if(unitsNum > colNum * rowNum / 2 || unitsNum == 0 || colNum == 0 || rowNum == 0)
		THROW("Invalid grid constants. uNum=" << unitsNum << ", cNum=" << colNum << ", rNum=" << rowNum);

	_grid.resize(rowNum);

	for(CellInt row = 0; row < rowNum; ++row)
	{
		_grid.at(row).resize(colNum);
		std::vector<pCell>& rowVecRef = _grid.at(row);

		for(CellInt col = 0; col < colNum; ++col)
		{
			pCell cell;
			uint16_t cellTypeInt;

			if(!(ss >> cellTypeInt))
				THROW("Error while reading grid");

			cell = std::make_shared<Cell>(Cell::intToCellType(cellTypeInt), col, row);
			rowVecRef.at(col) = cell;
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
	return _grid.at(row).at(col);
}

/***********************************************/
bool Grid::attackReachable(pCell c1, pCell c2) const
{
	auto dachiv = distanceAchievable(c1, c2);
	auto dist = std::get<0>(dachiv);
	bool achiv = std::get<1>(dachiv);

	return achiv && (dist <= c1->occupier()->moveRange() - 1 + c1->occupier()->attackRange());
}

/***********************************************/
pRoute Grid::buildRoute(pCell c1, pCell c2) const
{
	pCell curr = c1;
	std::set<pCell> visited;
	std::vector<pCell> visitedvec;
	pUnit attacker = c1->occupier();
	pRoute route = std::make_shared<Route>(curr, attacker);

	visited.insert(curr);
	visitedvec.push_back(curr);

	while((curr->row() != c2->row() || curr->column() != c2->column()) && attacker->moveRange() > route->length())
	{
		auto sortfunct = [c1, c2](pCell lc1, pCell lc2) -> bool
		{
			if(lc1->occupier() || lc2->occupier())
			{
				if(!lc1->occupier())
					return true;
				else if(!lc2->occupier())
					return false;

				if(lc1->occupier()->owner() == lc2->occupier()->owner())
					return fdistance(lc1, c2) < fdistance(lc2, c2);

				//we can't go through friend, yet we can attack through enemy
				if(lc1->occupier()->owner() == c1->occupier()->owner())
					return false;
				else
					return true;
			}

			return fdistance(lc1, c2) < fdistance(lc2, c2);
		};
		std::set<pCell, decltype(sortfunct)> availableMoves(sortfunct); // first element is closest to dest.

		//bidlokod:
		if(exists(curr->column() + 1, curr->row()) && at(curr->column() + 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() + 1, curr->row()));

		if(exists(curr->column(), curr->row() + 1) && at(curr->column(), curr->row() + 1)->occupiable() && visited.find(at(curr->column(), curr->row() + 1)) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() + 1));

		if(exists(curr->column() - 1, curr->row()) && at(curr->column() - 1, curr->row())->occupiable() && visited.find(at(curr->column() - 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() - 1, curr->row()));

		if(exists(curr->column(), curr->row() - 1) && at(curr->column(), curr->row() - 1)->occupiable() && visited.find(at(curr->column(), curr->row() - 1)) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() - 1));

		if(availableMoves.empty())
		{
			qWarning() << "no available moves ._.";
			break;
		}

		curr = *(availableMoves.begin());
		visited.insert(curr);
		visitedvec.push_back(curr);

		if(curr->occupier() && curr->occupier()->owner() == c1->occupier()->owner())
		{
			qWarning() << "ally on chosen move; stopping right here";
			break;
		}
		else
			route->addCell(curr);
	}

	return route;
}

/***********************************************/
CellInt Grid::colNum() const
{
	return _grid.at(0).size();
}

/***********************************************/
RangeInt Grid::distance(const pCell& c1, const pCell& c2)
{
	return std::abs(c1->column() - c2->column()) + std::abs(c1->row() - c2->row());
}

/***********************************************/
double Grid::fdistance(const pCell& c1, const pCell& c2)
{
	return std::fabs(c1->column() - c2->column()) + std::fabs(c1->row() - c2->row());
}

/***********************************************/
std::tuple<RangeInt, bool> Grid::distanceAchievable(pCell c1, pCell c2) const
{
	uint8_t dist = 0;
	pCell curr = c1;
	std::set<pCell> visited;
	bool achievable = true;

	visited.insert(curr);

	while(curr != c2)
	{
		auto sortfunct = [c1, c2](const pCell& lc1, const pCell& lc2) -> bool
		{
			if(lc1->occupier() || lc2->occupier())
			{
				if(!lc1->occupier())
					return true;
				else if(!lc2->occupier())
					return false;

				if(lc1->occupier()->owner() == lc2->occupier()->owner())
					return false;

				//we can't go through friend, yet we can attack through enemy
				if(lc1->occupier()->owner() == c1->occupier()->owner())
					return false;
				else
					return true;
			}

			return fdistance(lc1, c2) < fdistance(lc2, c2);
		};
		std::set<pCell, decltype(sortfunct)> availableMoves(sortfunct); // first element is closest to dest.

		//bidlokod:
		if(exists(curr->column() + 1, curr->row()) && at(curr->column() + 1, curr->row())->occupiable() && visited.find(at(curr->column() + 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() + 1, curr->row()));

		if(exists(curr->column(), curr->row() + 1) && at(curr->column(), curr->row() + 1)->occupiable() && visited.find(at(curr->column(), curr->row() + 1)) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() + 1));

		if(exists(curr->column() - 1, curr->row()) && at(curr->column() - 1, curr->row())->occupiable() && visited.find(at(curr->column() - 1, curr->row())) == visited.end())
			availableMoves.insert(at(curr->column() - 1, curr->row()));

		if(exists(curr->column(), curr->row() - 1) && at(curr->column(), curr->row() - 1)->occupiable() && visited.find(at(curr->column(), curr->row() - 1)) == visited.end())
			availableMoves.insert(at(curr->column(), curr->row() - 1));

		if(availableMoves.empty())
		{
			qWarning() << "No available moves";
			achievable = false;
			break;
		}

		curr = *(availableMoves.begin());
		visited.insert(curr);
		++dist;

		//if ally we stop
		if(curr->occupier() && curr->occupier()->owner() == c1->occupier()->owner())
		{
			qDebug() << dist << " - ally on chosen move";
			achievable = false;
			break;
		}
	}

	return std::make_tuple(dist, achievable);
}

/***********************************************/
pGrid Grid::getEmptyCopy() const
{
	pGrid copy(new Grid);
	size_t row = 0;

	copy->_grid.resize(rowNum());

	for(auto const& rowVecRef : _grid)
	{
		size_t col = 0;
		auto& rowCopiedVecRef = copy->_grid.at(row++);

		rowCopiedVecRef.resize(colNum());

		for(auto const& cellRef : rowVecRef)
			rowCopiedVecRef.at(col++) = cellRef->getEmptyCopy();
	}

	return copy;
}

/***********************************************/
std::tuple<CellInt, CellInt, CellInt, CellInt> Grid::startingLeftSideRect() const
{
	CellInt tlRow = 0;
	CellInt tlCol = 0;
	CellInt brRow = 0;
	CellInt brCol = 0;

	for(const auto& vref : _grid)
	{
		for(const auto& cref : vref)
		{
			if(cref->cellType() == CellType::LeftStartingArea)
			{
				const auto& row = cref->row();
				const auto& col = cref->column();

				tlRow = std::min(row, tlRow);
				tlCol = std::min(col, tlCol);

				brRow = std::max(row, brRow);
				brCol = std::max(col, brCol);
			}
		}
	}

	return std::make_tuple(tlRow, tlCol, brRow, brCol);
}

/***********************************************/
bool Grid::exists(const CellInt col, const CellInt row) const
{
	if(col >= 0 && col < colNum() && row >= 0 && row < rowNum())
		return true;
	else
		return false;
}

/***********************************************/
CellInt Grid::rowNum() const
{
	return _grid.size();
}

/***********************************************/
void Grid::setState(const GridState newstate, pPlayer permissionRecipient)
{
	bool stateChanged = false;

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
				THROW("No _permissionOwner set 1");

			break;
		}
		case(GridState::RightPlayerPlacing):
		{
			if(state() != GridState::LeftPlayerPlacing)
				THROW("Impossible state change 2");

			if(!_permissionOwner)
				THROW("No _permissionOwner set 2");

			break;
		}
		case(GridState::Turn):
		{
			if(state() != GridState::RightPlayerPlacing && state() != GridState::Turn)
				THROW("Impossible state change 3");

			if(!_permissionOwner)
				THROW("No _permissionOwner set 3");

			break;
		}
	}

	stateChanged = _state != newstate;
	_state = newstate;

	if(_callbackSet && stateChanged)
	{
		qDebug() << "state changed; callbackin'";
		_onStateChangeCallback();
	}
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
void Grid::setOnStateChangeCallback(std::function<void ()> cback)
{
	_onStateChangeCallback = cback;
	_callbackSet = true;
}

/***********************************************/
Grid::Grid()
{

}

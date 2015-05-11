/*--------------------------------------------------------------------------*/
#include <sstream>
/*--------------------------------------------------------------------------*/
#include "Grid.h"
#include "Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Grid::Grid(const std::string& init)
{
	CellInt colNum = 0;
	CellInt rowNum = 0;
	std::stringstream ss(init);

	if(!(ss >> colNum >> rowNum))
		THROW("Error while reading size of grid");

	if(colNum == 0 || rowNum == 0)
		THROW("Invalid size of grid. cNum=" << colNum << ", rNum=" << rowNum);

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

			cell = pCell(new Cell(Cell::intToCellType(cellTypeInt)));
			columnVecRef.push_back(cell);
		}
	}
}

/***********************************************/
Grid::~Grid()
{

}

/***********************************************/
pCell Grid::at(const CellInt col, const CellInt row) const
{
	return _grid.at(col).at(row);
}

/***********************************************/
CellInt Grid::colNum() const
{
	return _grid.size();
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
}

/***********************************************/
CellInt Grid::rowNum() const
{
	return _grid.at(0).size();
}

/***********************************************/
bool Grid::setState(const GridState newstate, pPlayer permissionRecipient)
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
Grid::Grid()
{

}

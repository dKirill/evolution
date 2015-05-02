/*--------------------------------------------------------------------------*/
#include <sstream>
/*--------------------------------------------------------------------------*/
#include "Grid.h"
#include "Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Grid::Grid(const std::string& init)
{
	uint16_t colNum = 0;
	uint16_t rowNum = 0;
	std::stringstream ss(init);

	if(!(ss >> colNum >> rowNum))
		THROW("Error while reading size of grid");

	if(colNum == 0 || rowNum == 0)
		THROW("Invalid size of grid. cNum=" << colNum << ", rNum=" << rowNum);

	_grid.reserve(colNum);

	for(uint16_t col = 0; col < colNum; ++col)
	{
		_grid.at(col).reserve(rowNum);
		std::vector<pCell>& columnVecRef = _grid.at(col);

		for(uint16_t row = 0; row < rowNum; ++row)
		{
			pCell cell;
			uint8_t cellTypeInt;

			if(!(ss >> cellTypeInt))
				THROW("Error while reading grid");

			cell = pCell(new Cell(intToCellType(cellTypeInt)));
			columnVecRef.push_back(cell);
		}
	}
}

/***********************************************/
Grid::~Grid()
{

}

/***********************************************/
uint16_t Grid::colNum() const
{
	return _grid.size();
}

/***********************************************/
pGrid Grid::getEmptyCopy() const
{
	pGrid copy(new Grid);
	size_t col = 0;

	copy->_grid.reserve(colNum());

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
uint16_t Grid::rowNum() const
{
	return _grid.at(0).size();
}

/***********************************************/
Grid::Grid()
{

}

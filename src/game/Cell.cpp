/*--------------------------------------------------------------------------*/
#include "game/Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Cell::Cell(const CellType cellType_, const CellInt col, const CellInt row) : _cellType(cellType_), _column(col), _row(row)
{

}

/***********************************************/
Cell::~Cell()
{

}

/***********************************************/
CellType Cell::cellType() const
{
	return _cellType;
}

/***********************************************/
CellInt Cell::column() const
{
	return _column;
}

/***********************************************/
CellType Cell::intToCellType(const uint8_t intval)
{
	switch(intval)
	{
		case(0):
			return CellType::Flat;
		case(1):
			return CellType::Mountain;
		case(2):
			return CellType::LeftStartingArea;
		case(3):
			return CellType::RightStartingArea;
	}

	THROW("No CellType for intval=" << intval);
}

/***********************************************/
bool Cell::occupiable() const
{
	switch(cellType())
	{
		case(CellType::Flat):
		case(CellType::LeftStartingArea):
		case(CellType::RightStartingArea):
			return true;
		case(CellType::Mountain):
			return false;
	}
}

/***********************************************/
pUnit Cell::occupier() const
{
	return _occupier;
}

/***********************************************/
CellInt Cell::row() const
{
	return _row;
}

/***********************************************/
void Cell::free()
{
	_occupier.reset();
}

/***********************************************/
pCell Cell::getEmptyCopy() const
{
	return std::make_shared<Cell>(cellType(), column(), row());
}

/***********************************************/
void Cell::occupy(pUnit entering)
{
	if(occupiable() == false)
		THROW("Attempt to occupy unoccupiable cell");

	_occupier = entering;
}

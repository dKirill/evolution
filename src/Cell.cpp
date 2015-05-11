/*--------------------------------------------------------------------------*/
#include "Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Cell::Cell(const CellType cellType_) : _cellType(cellType_)
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
void Cell::free()
{
	_occupier.reset();
}

/***********************************************/
pCell Cell::getEmptyCopy() const
{
	return pCell(new Cell(cellType()));
}

/***********************************************/
void Cell::occupy(pUnit entering)
{
	if(occupiable() == false)
		THROW("Attempt to occupy unoccupiable cell");

	_occupier = entering;
}

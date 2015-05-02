/*--------------------------------------------------------------------------*/
#include "Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Cell::Cell(const CellType cellType) : _cellType(cellType)
{
	if(cellType() > 3)
		THROW("Invalid cell type");
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
bool Cell::free()
{
	if(occupiable() == false || !occupier())
		return false;

	_occupier.reset();

	return true;
}

/***********************************************/
pCell Cell::getEmptyCopy() const
{
	return pCell(new Cell(cellType()));
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
bool Cell::occupy(pUnit entering)
{
	if(occupiable() == false || occupier())
		return false;

	_occupier = entering;

	return true;
}

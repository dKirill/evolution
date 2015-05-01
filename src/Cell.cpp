/*--------------------------------------------------------------------------*/
#include "Cell.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Cell::Cell(uint16_t cellType)
{
	switch(cellType)
	{
		case(0):
			_canBeEntered = true;
			break;
		case(1):
			_canBeEntered = false;
			break;
		default:
			THROW("Invalid cell type");
	}
}

/***********************************************/
Cell::~Cell()
{

}

/***********************************************/
bool Cell::canBeEntered()
{
	return _canBeEntered;
}

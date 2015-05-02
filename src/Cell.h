#ifndef CELL_H
#define CELL_H

/*--------------------------------------------------------------------------*/
#include <boost/noncopyable.hpp>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

//cell types
enum class CellType : uint8_t
{
	Flat = 0,
	Mountain = 1,
	LeftStartingArea = 2,
	RightStartingArea = 3
};

class Cell : public boost::noncopyable
{
public:
	Cell(const CellType cellType);

	~Cell();

	CellType cellType() const;
	pCell getEmptyCopy() const;
	bool free();
	static CellType intToCellType(const uint8_t intval);
	bool occupiable() const;
	pUnit occupier() const;
	bool occupy(pUnit entering);

private:
	CellType _cellType;
	pUnit _occupier;
};

#endif // CELL_H

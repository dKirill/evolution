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
	Cell(const CellType cellType_);

	~Cell();

	CellType cellType() const;
	static CellType intToCellType(const uint8_t intval);
	bool occupiable() const;
	pUnit occupier() const;

private:
	void free();
	pCell getEmptyCopy() const;
	void occupy(pUnit entering);

	CellType _cellType;
	pUnit _occupier;

	friend class Game;
};

#endif // CELL_H

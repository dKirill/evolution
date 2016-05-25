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
	Cell(const CellType cellType_, const CellInt col, const CellInt row);

	~Cell();

	CellType cellType() const;
	CellInt column() const;
	static CellType intToCellType(const uint16_t intval);
	bool occupiable() const;
	pUnit occupier() const;
	CellInt row() const;

private:
	void free();
	pCell getEmptyCopy() const;
	void occupy(pUnit entering);

	CellType _cellType = CellType::Mountain;
	CellInt _column = 0;
	pUnit _occupier;
	CellInt _row = 0;

	friend class Game;
	friend class Grid;
	friend class Individual; // //.-
};

#endif // CELL_H

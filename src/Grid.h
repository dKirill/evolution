#ifndef GRID_H
#define GRID_H

/*--------------------------------------------------------------------------*/
#include <vector>
/*--------------------------------------------------------------------------*/
#include <boost/noncopyable.hpp>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class GridState : uint8_t
{
	Initial,
	LeftPlayerPlacing,
	RightPlayerPlacing,
	Turn
};

class Grid : public boost::noncopyable
{
public:
	/**Init string template:

	   C R a11 a12 a21 a22

	   Where C - num of columns, R - num of rows, a## - type of surface (0 ~ flat, 1 ~ mountain, 2 ~ left starting area, 3 ~ right starting area)
	*/
	Grid(const std::string& init);
	~Grid();

	uint16_t colNum() const;
	pGrid getEmptyCopy() const;
	uint16_t rowNum() const;
	GridState state() const;

private:
	Grid();

	std::vector<std::vector<pCell>> _grid;
	GridState _state;
};

#endif // GRID_H

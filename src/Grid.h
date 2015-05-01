#ifndef GRID_H
#define GRID_H

/*--------------------------------------------------------------------------*/
#include <vector>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Grid
{
public:
	/**Init string template:

	   C R a11 a12 a21 a22

	   Where C - num of columns, R - num of rows, a## - type of surface (0 ~ flat, 1 ~ mountain)
	*/
	Grid(const std::string& init);
	~Grid();

	uint16_t colNum() const;
	uint16_t rowNum() const;

private:
	std::vector<std::vector<pCell>> _grid;
};

#endif // GRID_H

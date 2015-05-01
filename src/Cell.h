#ifndef CELL_H
#define CELL_H

#include "Global.h"

class Cell
{
public:
	Cell(uint16_t cellType);

	~Cell();

	bool canBeEntered();

private:
	bool _canBeEntered;
};

#endif // CELL_H

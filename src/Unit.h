#ifndef UNIT_H
#define UNIT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Unit
{
public:
	Unit(pPlayer owner_);
	~Unit();

	pPlayer owner() const;

private:
	pPlayer _owner;
};

#endif // UNIT_H

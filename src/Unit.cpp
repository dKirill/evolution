/*--------------------------------------------------------------------------*/
#include "Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Unit::Unit(pPlayer owner, const Units type) : _owner(owner), _type(type)
{
	switch(type)
	{
		//TODO init constants
	}
}

/***********************************************/
Unit::~Unit()
{

}

/***********************************************/
AttackInt Unit::attack() const
{
	return _attack; //TODO calc according to health %
}

/***********************************************/
AttackSpreadFloat Unit::attackSpread() const
{
	return _attackSpread;
}

/***********************************************/
HealthInt Unit::health() const
{
	return _health;
}

/***********************************************/
pPlayer Unit::owner() const
{
	return _owner;
}

/***********************************************/
RangeInt Unit::range() const
{
	return _range;
}

/***********************************************/
Units Unit::type() const
{
	return _type;
}


/*--------------------------------------------------------------------------*/
#include "Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Unit::Unit(pPlayer owner, const Units type_) : _owner(owner), _type(type_)
{
	switch(type())
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
	return _attack;
}

/***********************************************/
ModifierFloat Unit::attackModifier(const Units victim) const
{
	switch(type())
	{
		switch(victim)
		{
			//TODO init constants
		}
	}
}

/***********************************************/
RangeInt Unit::attackRange() const
{
	return _attackRange;
}

/***********************************************/
ModifierFloat Unit::attackSpread() const
{
	return _attackSpread;
}

/***********************************************/
HealthInt Unit::baseHealth() const
{
	return _baseHealth;
}

/***********************************************/
HealthInt Unit::health() const
{
	return _health;
}

/***********************************************/
RangeInt Unit::moveRange() const
{
	return _moveRange;
}

/***********************************************/
pPlayer Unit::owner() const
{
	return _owner;
}

/***********************************************/
Units Unit::type() const
{
	return _type;
}


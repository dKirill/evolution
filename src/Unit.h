#ifndef UNIT_H
#define UNIT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class Units : uint8_t
{
	Archer,
	Horseman,
	Pikeman,
	Swordsman
};

class Unit
{
public:
	Unit(pPlayer owner, const Units type);
	~Unit();

	AttackInt attack() const;
	AttackSpreadFloat attackSpread() const;
	HealthInt health() const;
	pPlayer owner() const;
	RangeInt range() const;
	Units type() const;

private:
	AttackInt _attack;
	AttackSpreadFloat _attackSpread;
	HealthInt _health;
	pPlayer _owner;
	RangeInt _range;
	Units _type;
};

#endif // UNIT_H

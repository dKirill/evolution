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
	Unit(pPlayer owner, const Units type_);
	~Unit();

	AttackInt attack() const;
	ModifierFloat attackModifier(const Units victim) const;
	RangeInt attackRange() const;
	ModifierFloat attackSpread() const;
	HealthInt baseHealth() const;
	HealthInt health() const;
	RangeInt moveRange() const;
	pPlayer owner() const;
	Units type() const;

private:
	AttackInt _attack;
	RangeInt _attackRange;
	ModifierFloat _attackSpread;
	HealthInt _baseHealth;
	HealthInt _health;
	RangeInt _moveRange;
	pPlayer _owner;
	Units _type;
};

#endif // UNIT_H

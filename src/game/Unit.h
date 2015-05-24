#ifndef UNIT_H
#define UNIT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class UnitsType : uint8_t
{
	Archer,
	Horseman,
	Pikeman,
	Swordsman
};

class Unit
{
public:
	Unit(pPlayer owner, const UnitsType type_);
	~Unit();

	bool alive() const;
	ModifierFloat attackModifier(const UnitsType victim) const;
	RangeInt attackRange() const;
	ModifierFloat attackSpread() const;
	HealthInt baseHealth() const;
	void damage(const AttackInt amount); //damage this unit
	HealthInt health() const;
	RangeInt moveRange() const;
	AttackFloat nextAttack(RandEngine& reng);
	pPlayer owner() const;
	UnitsType type() const;

private:
	AttackInt attack() const;

	AttackInt _attack = 0;
	RangeInt _attackRange = 0;
	ModifierFloat _attackSpread = 0;
	HealthInt _baseHealth = 0;
	HealthInt _health = 0;
	RangeInt _moveRange = 0;
	std::normal_distribution<ModifierFloat> _normalDist;
	pPlayer _owner;
	UnitsType _type;
};

#endif // UNIT_H

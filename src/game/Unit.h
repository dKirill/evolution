#ifndef UNIT_H
#define UNIT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class UnitType : uint8_t
{
	Archer = 0,
	Horseman = 1,
	Pikeman = 2,
	Swordsman = 3
};

class Unit
{
public:
	Unit(pPlayer owner, const UnitType type_);
	~Unit();

	bool alive() const;
	ModifierFloat attackModifier(const UnitType victim) const;
	RangeInt attackRange() const;
	ModifierFloat attackSpread() const;
	HealthInt baseHealth() const;
	void damage(const AttackInt amount); //damage this unit
	HealthInt health() const;
	RangeInt moveRange() const;
	AttackFloat nextAttack(RandEngine& reng);
	pPlayer owner() const;
	UnitType type() const;

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
	UnitType _type;
};

#endif // UNIT_H

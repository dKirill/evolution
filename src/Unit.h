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

	bool alive() const;
	ModifierFloat attackModifier(const Units victim) const;
	RangeInt attackRange() const;
	ModifierFloat attackSpread() const;
	HealthInt baseHealth() const;
	void damage(const AttackInt amount); //damage this unit
	HealthInt health() const;
	RangeInt moveRange() const;
	AttackFloat nextAttack(RandEngine& reng);
	pPlayer owner() const;
	Units type() const;

private:
	AttackInt attack() const;

	AttackInt _attack;
	RangeInt _attackRange;
	ModifierFloat _attackSpread;
	HealthInt _baseHealth;
	HealthInt _health;
	RangeInt _moveRange;
	std::normal_distribution<ModifierFloat> _normalDist;
	pPlayer _owner;
	Units _type;
};

#endif // UNIT_H

/*--------------------------------------------------------------------------*/
#include "game/Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Unit::Unit(pPlayer owner, const UnitsType type_) : _owner(owner), _type(type_)
{
	switch(type())
	{
		case(UnitsType::Archer): //TODO config?!
		{
			_attack = 5000;
			_attackRange = 2;
			_attackSpread = 0.3;
			_baseHealth = 10000;
			_moveRange = 3;

			break;
		}
		case(UnitsType::Horseman):
		{
			_attack = 7000;
			_attackRange = 1;
			_attackSpread = 0.3;
			_baseHealth = 12500;
			_moveRange = 5;

			break;
		}
		case(UnitsType::Pikeman):
		{
			_attack = 5000;
			_attackRange = 1;
			_attackSpread = 0.1;
			_baseHealth = 15000;
			_moveRange = 4;

			break;
		}
		case(UnitsType::Swordsman):
		{
			_attack = 6000;
			_attackRange = 1;
			_attackSpread = 0.2;
			_baseHealth = 17500;
			_moveRange = 3;

			break;
		}
	}

	_health = _baseHealth;
	_normalDist.param(std::normal_distribution<ModifierFloat>::param_type(attack(), attack() * attackSpread() / 3.0));
}

/***********************************************/
Unit::~Unit()
{

}

/***********************************************/
bool Unit::alive() const
{
	return health() > 0;
}

/***********************************************/
ModifierFloat Unit::attackModifier(const UnitsType victim) const
{
	switch(type())
	{
		case(UnitsType::Archer):
		{
			switch(victim)
			{
				case(UnitsType::Archer): //TODO config?!
					return 1.2;
				case(UnitsType::Horseman):
					return 1.1;
				case(UnitsType::Pikeman):
					return 1.1;
				case(UnitsType::Swordsman):
					return 1;
			}
		}
		case(UnitsType::Horseman):
		{
			switch(victim)
			{
				case(UnitsType::Archer):
					return 2;
				case(UnitsType::Horseman):
					return 1;
				case(UnitsType::Pikeman):
					return 0.7;
				case(UnitsType::Swordsman):
					return 1.5;
			}
		}
		case(UnitsType::Pikeman):
		{
			switch(victim)
			{
				case(UnitsType::Archer):
					return 1.2;
				case(UnitsType::Horseman):
					return 1.5;
				case(UnitsType::Pikeman):
					return 1;
				case(UnitsType::Swordsman):
					return 0.8;
			}
		}
		case(UnitsType::Swordsman):
		{
			switch(victim)
			{
				case(UnitsType::Archer):
					return 1.2;
				case(UnitsType::Horseman):
					return 1;
				case(UnitsType::Pikeman):
					return 1.2;
				case(UnitsType::Swordsman):
					return 1;
			}
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
void Unit::damage(const AttackInt amount)
{
	_health -= amount;
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
AttackFloat Unit::nextAttack(RandEngine& reng)
{
	return _normalDist(reng);
}

/***********************************************/
pPlayer Unit::owner() const
{
	return _owner;
}

/***********************************************/
UnitsType Unit::type() const
{
	return _type;
}

/***********************************************/
AttackInt Unit::attack() const
{
	return _attack;
}


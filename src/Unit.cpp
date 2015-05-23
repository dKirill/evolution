/*--------------------------------------------------------------------------*/
#include "Unit.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Unit::Unit(pPlayer owner, const Units type_) : _owner(owner), _type(type_)
{
	switch(type())
	{
		case(Units::Archer): //TODO config?!
		{
			_attack = 5000;
			_attackRange = 2;
			_attackSpread = 0.3;
			_baseHealth = 10000;
			_moveRange = 3;

			break;
		}
		case(Units::Horseman):
		{
			_attack = 7000;
			_attackRange = 1;
			_attackSpread = 0.3;
			_baseHealth = 12500;
			_moveRange = 5;

			break;
		}
		case(Units::Pikeman):
		{
			_attack = 5000;
			_attackRange = 1;
			_attackSpread = 0.1;
			_baseHealth = 15000;
			_moveRange = 4;

			break;
		}
		case(Units::Swordsman):
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
ModifierFloat Unit::attackModifier(const Units victim) const
{
	switch(type())
	{
		case(Units::Archer):
		{
			switch(victim)
			{
				case(Units::Archer): //TODO config?!
					return 1.2;
				case(Units::Horseman):
					return 1.1;
				case(Units::Pikeman):
					return 1.1;
				case(Units::Swordsman):
					return 1;
			}
		}
		case(Units::Horseman):
		{
			switch(victim)
			{
				case(Units::Archer):
					return 2;
				case(Units::Horseman):
					return 1;
				case(Units::Pikeman):
					return 0.7;
				case(Units::Swordsman):
					return 1.5;
			}
		}
		case(Units::Pikeman):
		{
			switch(victim)
			{
				case(Units::Archer):
					return 1.2;
				case(Units::Horseman):
					return 1.5;
				case(Units::Pikeman):
					return 1;
				case(Units::Swordsman):
					return 0.8;
			}
		}
		case(Units::Swordsman):
		{
			switch(victim)
			{
				case(Units::Archer):
					return 1.2;
				case(Units::Horseman):
					return 1;
				case(Units::Pikeman):
					return 1.2;
				case(Units::Swordsman):
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
Units Unit::type() const
{
	return _type;
}

/***********************************************/
AttackInt Unit::attack() const
{
	return _attack;
}


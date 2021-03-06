/*--------------------------------------------------------------------------*/
#include "Player.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Player::Player()
{
	static decltype(id()) _currid = 0;

	_id = _currid++;
}

/***********************************************/
quint32 Player::id() const
{
	return _id;
}

/***********************************************/
QString Player::name() const
{
	return _name;
}

/***********************************************/
void Player::setName(const QString& name)
{
	_name = name;
}

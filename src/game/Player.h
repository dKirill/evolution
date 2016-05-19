#ifndef PLAYER_H
#define PLAYER_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class Side : uint8_t
{
	Left,
	Right
};

class Player
{
public:
	Player();

	virtual void initGrid(pGame game, Side side) = 0;
	///only for view.
	virtual void initGrid(pGrid grid, Side side) = 0;
	virtual void turn(pGame game) = 0;

	quint32 id() const;
	QString name() const;
	void setName(const QString& name);

private:
	quint32 _id = 0;
	QString _name;
};

#endif // PLAYER_H


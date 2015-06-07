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
	virtual void initGrid(pGame game, Side side, RandEngine& reng) = 0;
	virtual void turn(pGame game) = 0;
};

#endif // PLAYER_H


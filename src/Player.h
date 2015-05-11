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
	~Player();

	void initGrid(pGrid grid, Side side);
	void turn(pGrid grid);

private:

};

#endif // PLAYER_H

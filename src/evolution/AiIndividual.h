#ifndef AIINDIVIDUAL_H
#define AIINDIVIDUAL_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
#include "game/Player.h"
/*--------------------------------------------------------------------------*/

class AiIndividual : public Player
{
public:
	AiIndividual();
	virtual ~AiIndividual();

	virtual void initGrid(pGame game, Side side);
	virtual void turn(pGame game);

private:

};

#endif // AIINDIVIDUAL_H

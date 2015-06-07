#ifndef AIINDIVIDUAL_H
#define AIINDIVIDUAL_H

/*--------------------------------------------------------------------------*/
#include "evolution/Gene.h"
#include "game/Player.h"
#include "Global.h"
/*--------------------------------------------------------------------------*/

class AiIndividual : public Player, public std::enable_shared_from_this<AiIndividual>
{
public:
	AiIndividual();
	virtual ~AiIndividual();

	virtual void initGrid(pGame game, Side side, RandEngine& reng) override;
	virtual void turn(pGame game) override;

private:
	std::vector<std::tuple<CellInt, CellInt, Gene>> _startingPositions; //1 dimension's enough
};

#endif // AIINDIVIDUAL_H

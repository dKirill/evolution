#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

/*--------------------------------------------------------------------------*/
#include <functional>
/*--------------------------------------------------------------------------*/
#include "evolution/Gene.h"
#include "game/Player.h"
#include "game/Unit.h"
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Individual : public Player, public std::enable_shared_from_this<Individual>
{
public:
	Individual(RandEngine& reng);
	virtual ~Individual() final;

	pIndividual evolve(RandEngine& reng);
	virtual void initGrid(pGame game, Side side) final;
	virtual void initGrid(pGrid grid, Side side) final;
	virtual void turn(pGame game) final;

private:
	Individual();

	void init(std::map<UnitType, Gene>& aps, RandEngine& reng);
	void initGrid(pGrid grid, Side side, std::function<void(pCell, pUnit)> placer, std::function<RandEngine&()> getRengine);

	std::map<UnitType, std::map<UnitType, Gene>> _attackPriorities;
	std::vector<std::tuple<CellInt, CellInt, Gene>> _startingPositions; //1 dimension's enough
};

#endif // Individual_H

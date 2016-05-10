#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

/*--------------------------------------------------------------------------*/
#include "evolution/Gene.h"
#include "game/Player.h"
#include "game/Unit.h"
#include "Global.h"
/*--------------------------------------------------------------------------*/

//global rand. eng.
//static RandEngine& globalReng() TODO saved for future use. delete later
//{
//	static RandEngine re;
//	static bool first = true;
//	static std::mutex mx;
//	std::lock_guard<std::mutex> guard(mx);

//	if(first)
//	{
//		re.seed((uint_fast32_t)std::time(NULL));
//		first = false;
//	}

//	return re;
//}

class Individual : public Player, public std::enable_shared_from_this<Individual>
{
public:
	Individual(RandEngine& reng);
	virtual ~Individual() final;

	pIndividual evolve(RandEngine& reng);
	virtual void initGrid(pGame game, Side side) final;
	virtual void turn(pGame game) final;

private:
	Individual();

	void init(std::map<UnitType, Gene>& aps, RandEngine& reng);

	std::map<UnitType, std::map<UnitType, Gene>> _attackPriorities;
	std::vector<std::tuple<CellInt, CellInt, Gene>> _startingPositions; //1 dimension's enough
};

#endif // Individual_H

#ifndef TOURNAMENT_H
#define TOURNAMENT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Tournament
{
public:
	Tournament(pGrid grid, const Players& players, const RoundInt roundsPerMatch);
	~Tournament();

	void run();
	pScoreTable scoreTable() const;

private:
	pGrid _grid;
	Matches _matches;
	Players _players;
	RoundInt _roundsPerMatch;
	pScoreTable _scoreTable;
};

#endif // TOURNAMENT_H

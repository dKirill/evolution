#ifndef TOURNAMENT_H
#define TOURNAMENT_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Tournament
{
public:
	Tournament(pGrid grid_, const Players& players, const RoundInt roundsPerMatch);
	~Tournament();

	pGrid grid() const;
	void run();
	pScoreTable scoreTable() const;

private:
	pGrid _grid;
	Matches _matches;
	Players _players;
	RoundInt _roundsPerMatch = 0;
	pScoreTable _scoreTable;
};

#endif // TOURNAMENT_H

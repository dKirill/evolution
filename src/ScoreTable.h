#ifndef SCORETABLE_H
#define SCORETABLE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum ScoreEnum
{
	Lose,
	Tie,
	Win
};

class ScoreTable
{
public:
	ScoreTable();
	~ScoreTable();

	void addPlayer(pPlayer player);
	void addScore(pPlayer player, ScoreEnum score);
	void merge(pScoreTable scoretable); //adds scoretable results to this
	void update(); //resort

private:
	Scores _scores;
};

#endif // SCORETABLE_H

#ifndef SCORETABLE_H
#define SCORETABLE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class ScoreEnum : uint8_t
{
	Lose = 0,
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
	Scores scores() const;

	//callback setter
	void setOnAnyChangeCallback(std::function<void()> cback);

private:
	bool _callbackSet = false;
	std::function<void()> _onAnyChange;
	Scores _scores;
};

#endif // SCORETABLE_H

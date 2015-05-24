#ifndef SCORE_H
#define SCORE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

struct FindByPlayer
{
	FindByPlayer(pPlayer player);

	bool operator()(pScore score);

private:
	pPlayer _player;
};

class Score
{
public:
	Score(pPlayer player_);
	~Score();

	void lose(const ScoreInt amount = 1);
	void tie(const ScoreInt amount = 1);
	void win(const ScoreInt amount = 1);
	pPlayer player() const;
	ScoreInt loses() const;
	ScoreInt ties() const;
	ScoreInt wins() const;

private:
	ScoreInt _loses = 0;
	pPlayer _player = 0;
	ScoreInt _ties = 0;
	ScoreInt _wins = 0;
};

bool operator<(pScore lscore, pScore rscore);

#endif // SCORE_H

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
	ScoreInt _loses;
	pPlayer _player;
	ScoreInt _ties;
	ScoreInt _wins;
};

bool operator<(pScore lscore, pScore rscore);

#endif // SCORE_H

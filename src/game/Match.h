#ifndef MATCH_H
#define MATCH_H

/*--------------------------------------------------------------------------*/
#include <QtCore/QRunnable>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/
#include <boost/throw_exception.hpp>
class Match : public QRunnable
{
public:
	Match(pGrid grid_, pPlayer player1_, pPlayer player2_, const RoundInt numOfRounds);
	~Match();

	pGrid grid() const;
	bool isOver() const;
	pPlayer player1() const;
	pPlayer player2() const;
	RoundInt roundsNum() const;
	RoundInt roundsPlayed() const;
	virtual void run();
	pScoreTable scoreTable() const;

private:
	pGrid _grid;
	pPlayer _player1;
	pPlayer _player2;
	uint8_t _roundsNum = 0;
	uint8_t _roundsPlayed = 0;
	pScoreTable _scoreTable = std::make_shared<ScoreTable>();
};

#endif // MATCH_H

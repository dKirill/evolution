#ifndef MATCH_H
#define MATCH_H

/*--------------------------------------------------------------------------*/
#include <QtCore/QRunnable>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Match : public QRunnable
{
public:
	Match(pGrid grid_, pPlayer player1_, pPlayer player2_, uint8_t numOfRounds);
	~Match();

	pGrid grid() const;
	bool isOver() const;
	pPlayer player1() const;
	pPlayer player2() const;
	uint8_t roundsNum() const;
	uint8_t roundsPlayed() const;
	virtual void run();
	pScoreTable scoreTable() const;

private:
	pGrid _grid;
	pPlayer _player1;
	pPlayer _player2;
	uint8_t _roundsNum;
	uint8_t _roundsPlayed;
	pScoreTable _scoreTable;
};

#endif // MATCH_H

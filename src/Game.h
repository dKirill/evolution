#ifndef GAME_H
#define GAME_H

/*--------------------------------------------------------------------------*/
#include <set>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Game
{
public:
	Game(pGrid grid_, pPlayer playerLeft_, pPlayer playerRight_, bool ftr, pScoreTable scoreTable);
	~Game();

	pGrid grid() const;
	pPlayer playerLeft() const;
	pPlayer playerRight() const;
	void run();
	pScoreTable scoreTable() const;

private:
	pPlayer nextPlayer() const;
	bool isOver();

	mutable pPlayer _currPlayer;
	bool _firstTurnRight;
	pGrid _grid;
	pPlayer _playerLeft;
	pPlayer _playerRight;
	pScoreTable _scoreTable;
};

#endif // GAME_H

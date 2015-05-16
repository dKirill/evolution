#ifndef GAME_H
#define GAME_H

/*--------------------------------------------------------------------------*/
#include <set>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Game : public std::enable_shared_from_this<Game>//TODO consider turn-history for visualizing
{
public:
	Game(pGrid grid_, pPlayer playerLeft_, pPlayer playerRight_, bool ftr, pScoreTable scoreTable);
	~Game();

	pGrid grid() const;
	void move(pRoute route);
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
	std::set<pUnit> _unitsMovedThisTurn;
};

#endif // GAME_H

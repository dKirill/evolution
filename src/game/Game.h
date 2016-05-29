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
	pPlayer playerLeft() const;
	pPlayer playerRight() const;
	void place(pCell cell, pUnit unit);
	///returns emptied cells
	pCell process(pRoute route);
	RandEngine& randEngine();
	void run();
	pScoreTable scoreTable() const;

private:
	bool attack(pCell src, pCell dest);
	AttackInt calcDamage(pUnit attacker, pUnit victim);
	bool isOver();
	static void move(pCell src, pCell dest);
	pPlayer nextPlayer() const;
	static std::uint32_t nextSeed();

	mutable pPlayer _currPlayer;
	bool _firstTurnRight = false;
	pGrid _grid;
	pPlayer _playerLeft;
	pPlayer _playerRight;
	RandEngine _rengine;
	pScoreTable _scoreTable;
	std::set<pUnit> _unitsMovedThisTurn;
};

#endif // GAME_H

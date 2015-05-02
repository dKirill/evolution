#ifndef GAME_H
#define GAME_H

/*--------------------------------------------------------------------------*/
#include <set>
/*--------------------------------------------------------------------------*/
#include <QtCore/QRunnable>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Game : public QRunnable
{
public:
	Game();
	~Game();

	pGrid grid() const;
	pPlayer playerLeft() const;
	pPlayer playerRight() const;
	virtual void run();
	void setGrid(pGrid grid);
	pPlayer setPlayerLeft(pPlayer player);
	pPlayer setPlayerRight(pPlayer player);

private:
	pGrid _grid;
	pPlayer _playerLeft;
	pPlayer _playerRight;
};

#endif // GAME_H

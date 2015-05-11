/*--------------------------------------------------------------------------*/
#include "Game.h"
#include "Match.h"
#include "ScoreTable.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Match::Match(pGrid grid_, pPlayer player1_, pPlayer player2_, uint8_t numOfRounds) : _grid(grid_), _player1(player1_), _player2(player2_), _roundsNum(numOfRounds), _roundsPlayed(0), _scoreTable(new ScoreTable)
{

}

/***********************************************/
Match::~Match()
{

}

/***********************************************/
pGrid Match::grid() const
{
	return _grid;
}

/***********************************************/
bool Match::isOver() const
{
	return roundsNum() == roundsPlayed();
}

/***********************************************/
pPlayer Match::player1() const
{
	return _player1;
}

/***********************************************/
pPlayer Match::player2() const
{
	return _player2;
}

/***********************************************/
uint8_t Match::roundsNum() const
{
	return _roundsNum;
}

/***********************************************/
uint8_t Match::roundsPlayed() const
{
	return _roundsPlayed;
}

/***********************************************/
void Match::run()
{
	while(isOver() == false)
	{
		Game game1(grid(), player1(), player2(), false, scoreTable());
		Game game2(grid(), player1(), player2(), true, scoreTable());

		game1.run();
		game2.run();
		++_roundsPlayed;
	}
}

/***********************************************/
pScoreTable Match::scoreTable() const
{
	return _scoreTable;
}

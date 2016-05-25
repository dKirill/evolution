/*--------------------------------------------------------------------------*/
#include "game/Game.h"
#include "game/Grid.h"
#include "game/Match.h"
#include "game/ScoreTable.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Match::Match(pGrid grid_, pPlayer player1_, pPlayer player2_, const RoundInt numOfRounds) : _grid(grid_), _player1(player1_), _player2(player2_), _roundsNum(numOfRounds)
{
	setAutoDelete(false);
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
RoundInt Match::roundsNum() const
{
	return _roundsNum;
}

/***********************************************/
RoundInt Match::roundsPlayed() const
{
	return _roundsPlayed;
}

/***********************************************/
void Match::run()
{
	qDebug() << "Match run";

	//2 games per round so each player starts first once
	while(isOver() == false)
	{
		auto game1 = std::make_shared<Game>(grid()->getEmptyCopy(), player1(), player2(), false, scoreTable());
		auto game2 = std::make_shared<Game>(grid()->getEmptyCopy(), player1(), player2(), true, scoreTable());

		game1->run();
		game2->run();
		++_roundsPlayed;
	}

	qDebug() << "Match run success";
}

/***********************************************/
pScoreTable Match::scoreTable() const
{
	return _scoreTable;
}

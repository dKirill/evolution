/*--------------------------------------------------------------------------*/
#include <QtCore/QThreadPool>
/*--------------------------------------------------------------------------*/
#include "game/Match.h"
#include "game/ScoreTable.h"
#include "game/Tournament.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Tournament::Tournament(pGrid grid, const Players& players, const RoundInt roundsPerMatch) : _grid(grid), _players(players), _roundsPerMatch(roundsPerMatch), _scoreTable(new ScoreTable)
{
	for(auto const& player1ref : _players)
	{
		for(auto const& player2ref : _players)
		{
			if(player1ref != player2ref)
				_matches.insert(pMatch(new Match(_grid, player1ref, player2ref, _roundsPerMatch)));
		}
	}
}

/***********************************************/
Tournament::~Tournament()
{

}

/***********************************************/
void Tournament::run()
{
	for(auto const& matchref : _matches)
	{
		QThreadPool::globalInstance()->start(matchref.get());
	}

	QThreadPool::globalInstance()->waitForDone();

	for(auto const& matchref : _matches)
	{
		if(!matchref->isOver())
		{
			qWarning() << "Match is not over yet";

			continue;
		}

		scoreTable()->merge(matchref->scoreTable());
	}

}

/***********************************************/
pScoreTable Tournament::scoreTable() const
{
	return _scoreTable;
}

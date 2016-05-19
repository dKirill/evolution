/*--------------------------------------------------------------------------*/
#include <QtCore/QThreadPool>
/*--------------------------------------------------------------------------*/
#include "game/Match.h"
#include "game/ScoreTable.h"
#include "game/Tournament.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Tournament::Tournament(pGrid grid_, const Players& players, const RoundInt roundsPerMatch) : _grid(grid_), _players(players), _roundsPerMatch(roundsPerMatch), _scoreTable(std::make_shared<ScoreTable>())
{
	for(auto const& player1ref : _players)
	{
		for(auto const& player2ref : _players)
		{
			if(player1ref != player2ref)
				_matches.insert(std::make_shared<Match>(grid(), player1ref, player2ref, _roundsPerMatch));
		}
	}
}

/***********************************************/
Tournament::~Tournament()
{

}

/***********************************************/
pGrid Tournament::grid() const
{
	return _grid;
}

/***********************************************/
void Tournament::run()
{
	qDebug() << "Tournament starts";
	//start every match in separate thread
	for(auto const& matchref : _matches)
	{
		QThreadPool::globalInstance()->start(matchref.get());
	}

	//wait for every thread to finish
	QThreadPool::globalInstance()->waitForDone();

	//check if every match is over. wait if it's not
	for(auto const& matchref : _matches)
	{
		if(!matchref->isOver())
		{
			qWarning() << "Match is not over yet";

			continue;
		}

		//merge finished match scoretable with general one
		scoreTable()->merge(matchref->scoreTable());
	}

	qDebug() << "Tournament ends";
}

/***********************************************/
pScoreTable Tournament::scoreTable() const
{
	return _scoreTable;
}

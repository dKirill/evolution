/*--------------------------------------------------------------------------*/
#include "game/Score.h"
#include "game/ScoreTable.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
ScoreTable::ScoreTable()
{

}

/***********************************************/
ScoreTable::~ScoreTable()
{

}

/***********************************************/
void ScoreTable::addPlayer(pPlayer player)
{
	if(std::find_if(_scores.begin(), _scores.end(), FindByPlayer(player)) != _scores.end())
		THROW("Player already presented");

	_scores.insert(pScore(new Score(player)));
}

/***********************************************/
void ScoreTable::addScore(pPlayer player, ScoreEnum score)
{
	auto foundIter = std::find_if(_scores.begin(), _scores.end(), FindByPlayer(player));

	if(foundIter != _scores.end())
	{
		switch(score)
		{
			case(ScoreEnum::Lose):
			{
				(*foundIter)->lose();
				break;
			}
			case(ScoreEnum::Tie):
			{
				(*foundIter)->tie();
				break;
			}
			case(ScoreEnum::Win):
			{
				(*foundIter)->win();
				break;
			}
		}
	}
	else
		THROW("Player not found");
}

/***********************************************/
void ScoreTable::merge(pScoreTable scoretable)
{
	for(auto const& scoreref : scoretable->_scores)
	{
		auto foundIter = std::find_if(_scores.begin(), _scores.end(), FindByPlayer(scoreref->player()));

		if(foundIter != _scores.end())
		{
			(*foundIter)->win(scoreref->wins());
			(*foundIter)->tie(scoreref->ties());
			(*foundIter)->lose(scoreref->loses());
		}
		else
			_scores.insert(scoreref);
	}
}

/***********************************************/
Scores ScoreTable::scores() const
{
	return _scores;
}

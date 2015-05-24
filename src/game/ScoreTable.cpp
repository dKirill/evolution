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
	for(auto const& scoreref : _scores)
	{
		if(scoreref->player() == player)
		{
			THROW("Player already presented");
		}
	}

	_scores.push_back(pScore(new Score(player)));
	update();
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
			}
			case(ScoreEnum::Tie):
			{
				(*foundIter)->tie();
			}
			case(ScoreEnum::Win):
			{
				(*foundIter)->win();
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
		bool found = false;

		for(auto const& thisscoreref : _scores)
		{
			if(scoreref->player() == thisscoreref->player()) //fp
			{
				thisscoreref->win(scoreref->wins());
				thisscoreref->tie(scoreref->ties());
				thisscoreref->lose(scoreref->loses());
				found = true;

				break;
			}
		}

		if(found == false)
			_scores.push_back(scoreref);
	}

	update();
}

/***********************************************/
void ScoreTable::update() //resort
{
	std::sort(_scores.begin(), _scores.end());
}

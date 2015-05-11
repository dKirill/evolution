/*--------------------------------------------------------------------------*/
#include "Score.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
FindByPlayer::FindByPlayer(pPlayer player) : _player(player)
{

}

/***********************************************/
bool FindByPlayer::operator()(pScore score)
{
	return _player == score->player();
}

/***********************************************/
/***********************************************/
Score::Score(pPlayer player_) : _loses(0), _player(player_), _ties(0), _wins(0)
{

}

/***********************************************/
Score::~Score()
{

}

/***********************************************/
void Score::lose()
{
	++_loses;
}

/***********************************************/
void Score::tie()
{
	++_ties;
}

/***********************************************/
void Score::win()
{
	++_wins;
}

/***********************************************/
pPlayer Score::player() const
{
	return _player;
}

/***********************************************/
ScoreInt Score::loses() const
{
	return _loses;
}

/***********************************************/
ScoreInt Score::ties() const
{
	return _ties;
}

/***********************************************/
ScoreInt Score::wins() const
{
	return _wins;
}

/***********************************************/
/***********************************************/
bool operator<(pScore lscore, pScore rscore)
{
	if(lscore->wins() > rscore->wins())
		return false;
	else if(lscore->wins() < rscore->wins())
		return true;

	if(lscore->ties() > rscore->ties())
		return false;
	else if(lscore->ties() < rscore->ties())
		return true;

	if(lscore->loses() > rscore->loses())
		return true;
	else if(lscore->loses() <= rscore->loses())
		return false;

	THROW("Error comparing scores");
}

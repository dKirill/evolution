/*--------------------------------------------------------------------------*/
#include "game/Score.h"
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
void Score::lose(const ScoreInt amount)
{
	_loses += amount;
}

/***********************************************/
void Score::tie(const ScoreInt amount)
{
	_ties += amount;
}

/***********************************************/
void Score::win(const ScoreInt amount)
{
	_wins += amount;
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
uint16_t Score::score() const
{
	return wins() * 3 + ties() * 1;
}


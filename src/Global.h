#ifndef GLOBAL_H
#define GLOBAL_H

/*--------------------------------------------------------------------------*/
#include <cstdint>
#include <exception>
#include <memory>
#include <set>
#include <sstream>
#include <vector>
/*--------------------------------------------------------------------------*/
#include <QtCore/QDebug>
/*--------------------------------------------------------------------------*/

//forward declarations
class Cell;
class Evolution;
class Game;
class Generation;
class Grid;
class Match;
class Player;
class Route;
class Score;
class ScoreTable;
class Tournament;
class Unit;

//ptr aliases
using pCell = std::shared_ptr<Cell>;
using pEvolution = std::shared_ptr<Evolution>;
using pGame = std::shared_ptr<Game>;
using pGeneration = std::shared_ptr<Generation>;
using pGrid = std::shared_ptr<Grid>;
using pMatch = std::shared_ptr<Match>;
using pPlayer = std::shared_ptr<Player>;
using pRoute = std::shared_ptr<Route>;
using pScore = std::shared_ptr<Score>;
using pScoreTable = std::shared_ptr<ScoreTable>;
using pTournament = std::shared_ptr<Tournament>;
using pUnit = std::shared_ptr<Unit>;

using AttackInt = uint16_t;
using CellInt = uint16_t;
using HealthInt = int32_t;
using RangeInt = uint8_t;
using RoundInt = uint8_t;
using ScoreInt = uint8_t;

using ModifierFloat = float;

using Matches = std::set<pMatch>;
using Players = std::set<pPlayer>;
using Scores = std::vector<pScore>;

//custom exception
class Exception : public std::exception
{
public:
	Exception(const std::string what_) _GLIBCXX_USE_NOEXCEPT : _what(what_) { }
	virtual ~Exception() _GLIBCXX_USE_NOEXCEPT { }

	/** Returns a C-style character string describing the general cause
	 *  of the current error.  */
	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT { return _what.c_str(); }

private:
	std::string _what;
};

//defines
#define THROW(x) { std::stringstream ss; ss << "Error: " << x << "; func: " << __PRETTY_FUNCTION__; throw Exception(ss.str()); }

#endif // GLOBAL_H


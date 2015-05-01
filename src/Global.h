#ifndef GLOBAL_H
#define GLOBAL_H

/*--------------------------------------------------------------------------*/
#include <cstdint>
#include <exception>
#include <memory>
#include <sstream>
/*--------------------------------------------------------------------------*/

//forward declarations
class Archer;
class Cell;
class Evolution;
class Generation;
class Grid;
class Knight;
class Match;
class Pikeman;
class Player;
class Swordsman;
class Tournament;
class Unit;

//ptr aliases
using pArcher = std::shared_ptr<Archer>;
using pCell = std::shared_ptr<Cell>;
using pEvolution = std::shared_ptr<Evolution>;
using pGeneration = std::shared_ptr<Generation>;
using pGrid = std::shared_ptr<Grid>;
using pKnight = std::shared_ptr<Knight>;
using pMatch = std::shared_ptr<Match>;
using pPikeman = std::shared_ptr<Pikeman>;
using pPlayer = std::shared_ptr<Player>;
using pSwordsman = std::shared_ptr<Swordsman>;
using pTournament = std::shared_ptr<Tournament>;
using pUnit = std::shared_ptr<Unit>;

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
#define THROW(x) { std::stringstream ss; ss << "Error: " << (x) << "; func: " __PRETTY_FUNCTION__; throw Exception(ss.str()); }

#endif // GLOBAL_H


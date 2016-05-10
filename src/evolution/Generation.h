#ifndef GENERATION_H
#define GENERATION_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
#include "game/Tournament.h"
/*--------------------------------------------------------------------------*/

class Generation
{
public:
	///first generation constructor; indis.size() shall be over 5 atleast (pref. 10++)
	Generation(pGrid grid, Individuals indis);

	///returns next gen
	pGeneration evolve(RandEngine& reng);
	GenerationInt generation() const;
	const Individuals& individuals() const;
	///might not exist
	pIndividual next() const;
	///casted indis
	Players players() const;
	///might not exist
	pIndividual previous() const;
	Tournament tournament() const;

private:
	///evolve constructor
	Generation(const Generation& prevgen, Individuals indis);

	GenerationInt _generation = 0;
	Individuals _individuals;
	pIndividual _next;
	pIndividual _previous;
	Tournament _tournament;
};

#endif // GENERATION_H

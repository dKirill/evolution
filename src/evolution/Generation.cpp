/*--------------------------------------------------------------------------*/
#include "evolution/Generation.h"
#include "evolution/Individual.h"
#include "game/Player.h"
#include "game/Score.h"
#include "game/ScoreTable.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Generation::Generation(pGrid grid, Individuals indis) : _generation(0), _individuals(indis), _tournament(grid, players(), 3) //TODO 3-conf
{

}

/***********************************************/
pGeneration Generation::evolve(RandEngine& reng)
{
	qDebug() << "evolve() starts";
	Individuals nextindis;
	pScoreTable stable;
	Scores scores;
	long double tier1fraction = 0.1;
	long double tier2fraction = 0.2;
	long double tier3fraction = 0.3;
	long double tier1nextmultiplier = 3;
	long double tier2nextmultiplier = 2;
	long double tier3nextmultiplier = 1;
	size_t nextindissize;
	size_t prevtier1size;
	size_t prevtier2size;
	size_t prevtier3size;
	size_t nexttier1size;
	size_t nexttier2size;
	size_t nexttier3size;

	//run tournament to evaluate individuals (!!uses threadpool)
	_tournament.run();

	//get final table
	stable = _tournament.scoreTable();
	scores = stable->scores();

	//calculate tier sizes
	nextindissize = scores.size();
	prevtier1size = std::ceil(nextindissize * tier1fraction);
	prevtier2size = std::ceil(nextindissize * tier2fraction);
	prevtier3size = std::ceil(nextindissize * tier3fraction);
	nexttier1size = prevtier1size * tier1nextmultiplier;
	//either calculated size, or remaining
	nexttier2size = std::min(prevtier2size * tier2nextmultiplier, static_cast<decltype(prevtier2size * tier2nextmultiplier)>(nextindissize - nexttier1size));
	nexttier3size = std::min(prevtier3size * tier3nextmultiplier, static_cast<decltype(prevtier3size * tier3nextmultiplier)>(nextindissize - nexttier2size - nexttier1size));

	if(nextindissize != nexttier1size + nexttier2size + nexttier3size)
		THROW("tier sizes miscalculated; nextindissize=" << nextindissize << " nexttier1size + nexttier2size + nexttier3size=" << (nexttier1size + nexttier2size + nexttier3size));

	//calculate next gen indis (mutate, etc)
	for(auto riter = scores.rbegin(); riter != scores.rend(); ++riter)
	{
		pIndividual indi;

		indi = std::dynamic_pointer_cast<Individual>((*riter)->player())->evolve(reng);
		nextindis.insert(indi);
	}

	qDebug() << "evolve() ends";
	return pGeneration(new Generation(*this, nextindis));
}

/***********************************************/
GenerationInt Generation::generation() const
{
	return _generation;
}

/***********************************************/
const Individuals& Generation::individuals() const
{
	return _individuals;
}

/***********************************************/
pIndividual Generation::next() const
{
	return _next;
}

/***********************************************/
Players Generation::players() const
{
	Players playas;
	const Individuals& indis = individuals();

	std::for_each(indis.cbegin(), indis.cend(), [&](Individuals::const_reference indiref) { playas.insert(std::dynamic_pointer_cast<Player>(indiref)); } );

	return playas;
}

/***********************************************/
pIndividual Generation::previous() const
{
	return _previous;
}

/***********************************************/
const Tournament& Generation::tournament() const
{
	return _tournament;
}

/***********************************************/
Generation::Generation(const Generation& prevgen, Individuals indis) : _generation(prevgen.generation() + 1), _individuals(indis), _tournament(prevgen.tournament().grid(), players(), 3) //TODO 3-conf
{

}

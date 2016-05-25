/*--------------------------------------------------------------------------*/
#include "evolution/Gene.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Gene::Gene(const float& mutationProbability_, const GeneInt min_, const GeneInt max_, const GeneInt value_) : _min(min_), _max(max_), _mutationProbability(mutationProbability_), _value(value_)
{
	if(value() > max() || value () < min() || mutationProbability() > 1 || mutationProbability() < 0)
		THROW("Invalid constants");
}

/***********************************************/
Gene::~Gene()
{

}

/***********************************************/
GeneInt Gene::max() const
{
	return _max;
}

/***********************************************/
GeneInt Gene::min() const
{
	return _min;
}

/***********************************************/
void Gene::mutate(RandEngine& reng)
{
	auto multiplier = 10000;
	std::uniform_int_distribution<GeneInt> uiDist;

	uiDist.param(std::uniform_int_distribution<GeneInt>::param_type(0, multiplier));

	//if mutation happens
	if(uiDist(reng) < mutationProbability() * multiplier)
	{
		std::normal_distribution<decltype(_mutationProbability)> normDist(mutationProbability(), 0.2);

		//mutate prime gen
		uiDist.param(std::uniform_int_distribution<GeneInt>::param_type(min(), max()));
		_value = uiDist(reng);

		//mutate probability of mutation
		_mutationProbability = std::max(0.05f, normDist(reng)); // we dont really want extremely low probability. too boring!
	}
}

/***********************************************/
GeneInt Gene::value() const
{
	return _value;
}

/***********************************************/
float Gene::mutationProbability() const
{
	return _mutationProbability;
}

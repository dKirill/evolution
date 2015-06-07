/*--------------------------------------------------------------------------*/
#include "evolution/Gene.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Gene::Gene(const GeneInt deviation_, const GeneInt max_, const GeneInt min_, const GeneInt value_) : _deviation(deviation_), _max(max_), _min(min_), _value(value_)
{
	if(value() > max() || value () < min())
		THROW("Invalid constants");
}

/***********************************************/
Gene::~Gene()
{

}

/***********************************************/
GeneInt Gene::deviation() const
{
	return _deviation;
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
GeneInt Gene::value() const
{
	return _value;
}

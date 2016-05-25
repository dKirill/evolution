#ifndef GENE_H
#define GENE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Gene
{
public:
	Gene(const float& mutationProbability, const GeneInt min_, const GeneInt max_, const GeneInt value_);
	~Gene();

	GeneInt max() const;
	GeneInt min() const;
	void mutate(RandEngine& reng);
	float mutationProbability() const;
	GeneInt value() const;

private:
	GeneInt _max = 0;
	GeneInt _min = 0;
	float _mutationProbability = 0;
	GeneInt _value = 0;
};

#endif // GENE_H

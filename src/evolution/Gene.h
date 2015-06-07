#ifndef GENE_H
#define GENE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Gene
{
public:
	Gene(const GeneInt deviation_, const GeneInt max_, const GeneInt min_, const GeneInt value_);
	~Gene();

	GeneInt deviation() const;
	GeneInt max() const;
	GeneInt min() const;
	GeneInt value() const;

private:
	GeneInt _deviation = 0;
	GeneInt _max = 0;
	GeneInt _min = 0;
	GeneInt _value = 0;
};

#endif // GENE_H

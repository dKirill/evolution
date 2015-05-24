#ifndef GENE_H
#define GENE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Gene
{
public:
	Gene();
	~Gene();

private:
	GeneInt _deviation = 0;
	GeneInt _max = 0;
	GeneInt _min = 0;
	GeneInt _value = 0;
};

#endif // GENE_H

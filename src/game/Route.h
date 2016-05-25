#ifndef ROUTE_H
#define ROUTE_H

/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Route
{
public:
	Route(pCell start, pUnit unit);
	~Route();

	void addCell(pCell cell);
	std::vector<pCell>::size_type length() const;
	std::vector<pCell> route() const;
	pUnit unit() const;

private:
	std::vector<pCell> _route;
	pUnit _unit;
};

#endif // ROUTE_H

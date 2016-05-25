/*--------------------------------------------------------------------------*/
#include "game/Route.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Route::Route(pCell start, pUnit unit) : _unit(unit)
{
	addCell(start);
}

/***********************************************/
Route::~Route()
{

}

/***********************************************/
void Route::addCell(pCell cell)
{
	_route.push_back(cell);
}

/***********************************************/
std::vector<pCell>::size_type Route::length() const
{
	return _route.size();
}

/***********************************************/
std::vector<pCell> Route::route() const
{
	return _route;
}

/***********************************************/
pUnit Route::unit() const
{
	return _unit;
}

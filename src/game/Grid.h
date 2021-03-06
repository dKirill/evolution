#ifndef GRID_H
#define GRID_H

/*--------------------------------------------------------------------------*/
#include <functional>
#include <vector>
/*--------------------------------------------------------------------------*/
#include <boost/noncopyable.hpp>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

enum class GridState : uint8_t
{
	Initial = 0,
	LeftPlayerPlacing,
	RightPlayerPlacing,
	Turn
};

class Grid : public boost::noncopyable
{
public:
	/**Init string template:

	   N C R a11 a12 a21 a22

	   Where N - num of units per player, C - num of columns, R - num of rows, a## - type of surface (0 ~ flat, 1 ~ mountain, 2 ~ left starting area, 3 ~ right starting area)
	*/
	Grid(const std::string& init);
	~Grid();

	static bool adjacency(pCell c1, pCell c2);
	pCell at(const CellInt col, const CellInt row) const;
	bool attackReachable(pCell c1, pCell c2) const;
	///returns route that might be incomplete if c2 is too far
	pRoute buildRoute(pCell c1, pCell c2) const;
	CellInt colNum() const;
	static RangeInt distance(const pCell& c1, const pCell& c2);
	static double fdistance(const pCell& c1, const pCell& c2);
	std::tuple<RangeInt, bool> distanceAchievable(pCell c1, pCell c2) const;
	bool exists(const CellInt col, const CellInt row) const;
	pGrid getEmptyCopy() const;
	///assumes it IS rect. for now.
	///rect(topLeftRow,topLeftCol,botRightRow,botRightCol)
	std::tuple<CellInt, CellInt, CellInt, CellInt> startingLeftSideRect() const;
	CellInt rowNum() const;
	void setState(const GridState newstate, pPlayer permissionRecipient = pPlayer());
	GridState state() const;
	UnitsInt unitsPerPlayer() const;

	//callback setter
	void setOnStateChangeCallback(std::function<void()> cback);

private:
	Grid();

	bool _callbackSet = false;
	std::vector<std::vector<pCell>> _grid;
	std::function<void()> _onStateChangeCallback;
	pPlayer _permissionOwner;
	GridState _state = GridState::Initial;
	UnitsInt _unitsPerPlayer = 0;
};

#endif // GRID_H

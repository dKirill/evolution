#ifndef GRIDVIEW_H
#define GRIDVIEW_H

/*--------------------------------------------------------------------------*/
#include <QtWidgets/QWidget>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

namespace Ui {
class GridView;
}

class GridView : public QWidget
{
	Q_OBJECT

public:
	explicit GridView(QWidget *parent = 0);
	~GridView();

	void dropGrid();
	void setGrid(pGrid grid);
	void update();

private:
	pGrid _grid;
	Ui::GridView* _ui;
};

#endif // GRIDVIEW_H

#ifndef GRAPHICSGRIDVIEW_H
#define GRAPHICSGRIDVIEW_H

/*--------------------------------------------------------------------------*/
#include <QWidget>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

namespace Ui {
class GraphicsGridView;
}

class GraphicsGridView : public QWidget
{
	Q_OBJECT

public:
	explicit GraphicsGridView(QWidget *parent = 0);
	~GraphicsGridView();

	void clear();
	///draws whole grid
	void drawGrid(pGrid grid);
	///draws specified rect of grid
	void drawGrid(pGrid grid, const CellInt topLeftRow, const CellInt topLeftCol, const CellInt botRightRow, const CellInt botRightCol);

private:
	Ui::GraphicsGridView* _ui;
};

#endif // GRAPHICSGRIDVIEW_H

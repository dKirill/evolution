/*--------------------------------------------------------------------------*/
#include "game/Grid.h"
#include "gui/GridView.h"
#include "ui_GridView.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
GridView::GridView(QWidget *parent) : QWidget(parent), _ui(new Ui::GridView)
{
	_ui->setupUi(this);
}

/***********************************************/
GridView::~GridView()
{
	delete _ui;
}

/***********************************************/
void GridView::dropGrid()
{
	_grid.reset();
}

/***********************************************/
void GridView::setGrid(pGrid grid)
{
	dropGrid();

	_grid = grid;
	_grid->setOnStateChangeCallback([this]() { this->update(); });
	update();
}

/***********************************************/
void GridView::update()
{
	if(!_grid)
	{
		qWarning() << "No update without _grid";
		return;
	}

	_ui->comboState->setCurrentIndex(static_cast<int>(_grid->state()));
	_ui->ggv->drawGrid(_grid);
	//TODO update players
}


/*--------------------------------------------------------------------------*/
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSimpleTextItem>
/*--------------------------------------------------------------------------*/
#include "game/Cell.h"
#include "game/Grid.h"
#include "game/Unit.h"
#include "gui/GraphicsGridView.h"
#include "ui_GraphicsGridView.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
GraphicsGridView::GraphicsGridView(QWidget* parent) : QWidget(parent), _ui(new Ui::GraphicsGridView)
{
	_ui->setupUi(this);
	_ui->gv->setScene(new QGraphicsScene);
}

/***********************************************/
GraphicsGridView::~GraphicsGridView()
{
	delete _ui;
}

/***********************************************/
void GraphicsGridView::drawGrid(pGrid grid)
{
	drawGrid(grid, 0, 0, grid->colNum() - 1, grid->rowNum() - 1);
}

/***********************************************/
void GraphicsGridView::drawGrid(pGrid grid, const CellInt topLeftCol, const CellInt topLeftRow, const CellInt botRightCol, const CellInt botRightRow)
{
	_ui->gv->scene()->clear();
	_ui->gv->scene()->setSceneRect(0, 0, _ui->gv->viewport()->width(), _ui->gv->viewport()->height());
	auto viewedColNum = botRightCol - topLeftCol;
	auto viewedRowNum = botRightRow - topLeftRow;
	auto horGap = _ui->gv->scene()->width() / viewedColNum;
	auto vertGap = _ui->gv->scene()->height() / viewedRowNum;
	QPen gridLinePen(Qt::black); //TODO conf?
	QPen mountainPen(Qt::darkBlue);
	QPen startingPen(Qt::lightGray);

	gridLinePen.setWidth(1);

	//draw hor grid lines
	for(auto x = horGap; x < _ui->gv->scene()->width(); x += horGap + gridLinePen.width())
		_ui->gv->scene()->addLine(x, 0, x, _ui->gv->scene()->height(), gridLinePen);

	//draw vert grid lines
	for(auto y = vertGap; y < _ui->gv->scene()->height(); y += vertGap + gridLinePen.width())
		_ui->gv->scene()->addLine(0, y, _ui->gv->scene()->width(), y, gridLinePen);

	//determine appropriate pxsize
	QFont font;
	int vpxsize = 1;
	int hpxsize = 1;
	int pxsize = 1;
	bool vfits = true;
	bool hfits = false;

	font.setPixelSize(vpxsize);

	//max vert px size
	while(vfits)
	{
		QFontMetrics fm(font);

		if(fm.height() > (vertGap - 2)) //2~margin
			vfits = false;
		else
		{
			++vpxsize;
			font.setPixelSize(vpxsize);
		}
	}

	//max hor px size
	while(hfits)
	{
		QFontMetrics fm(font);

		if(fm.width("W") > (horGap - 2)) //w is widest letter
			hfits = false;
		else
		{
			++hpxsize;
			font.setPixelSize(hpxsize);
		}
	}

	pxsize = std::min(hpxsize, vpxsize);
	font.setPixelSize(pxsize);

	//TODO consider redrawing
	//draw cell's insides
	for(auto col = topLeftCol; col < botRightCol; ++col)
	{
		for(auto row = topLeftRow; row < botRightRow; ++row)
		{
			pCell cell = grid->at(col, row);
			auto x = (horGap + gridLinePen.width()) * col;
			auto y = (vertGap + gridLinePen.width()) * row;

			//draw background of cells
			if(cell->cellType() == CellType::Mountain)
				_ui->gv->scene()->addRect(x, y, horGap, vertGap, mountainPen, QBrush(Qt::darkBlue));
			else if(cell->cellType() == CellType::LeftStartingArea || cell->cellType() == CellType::RightStartingArea)
				_ui->gv->scene()->addRect(x, y, horGap, vertGap, startingPen, QBrush(Qt::lightGray));

			//draw cell's occupier
			if(cell->occupier())
			{
				QGraphicsSimpleTextItem* textitem = new QGraphicsSimpleTextItem;

				textitem->setFont(font);

				switch(cell->occupier()->type())
				{
					case(UnitType::Archer):
					{
						textitem->setText("A");
						break;
					}
					case(UnitType::Horseman):
					{
						textitem->setText("H");
						break;
					}
					case(UnitType::Pikeman):
					{
						textitem->setText("P");
						break;
					}
					case(UnitType::Swordsman):
					{
						textitem->setText("S");
						break;
					}
				}

				_ui->gv->scene()->addItem(textitem);
				textitem->setPos(x, y);
			}
		}
	}
}


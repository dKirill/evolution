/*--------------------------------------------------------------------------*/
#include "evolution/Generation.h"
#include "evolution/Individual.h"
#include "game/Game.h"
#include "game/Grid.h"
#include "game/Player.h"
#include "gui/GenerationView.h"
#include "ui_GenerationView.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
GenerationView::GenerationView(QWidget* parent) : QWidget(parent), _ui(new Ui::GenerationView)
{
	_ui->setupUi(this);
	connect(_ui->stv, &ScoreTableView::selectionChanged, this, &GenerationView::selectionChanged);

	_ui->tw->setRowCount(4);
	_ui->tw->setColumnCount(4);
	_ui->tw->setHorizontalHeaderLabels(QStringList() << "Archer" << "Horseman" << "Pikeman" << "Swordsman");
	_ui->tw->setVerticalHeaderLabels(QStringList() << "Archer" << "Horseman" << "Pikeman" << "Swordsman");
}

/***********************************************/
GenerationView::~GenerationView()
{
	delete _ui;
}

/***********************************************/
void GenerationView::dropGeneration()
{
	_generation.reset();
	_grid.reset();
	update();
}

/***********************************************/
void GenerationView::setGeneration(const pGeneration& generation)
{
	_generation = generation;
	_grid = _generation->tournament().grid()->getEmptyCopy();
	update();
}

/***********************************************/
void GenerationView::update()
{
	_ui->spinGeneration->setValue(0);
	_ui->stv->dropScoreTable();
	_ui->ggv->clear();
	_ui->tw->clearContents();

	if(!_generation)
	{
		qWarning() << "no _generation == no update";
		return;
	}

	_ui->spinGeneration->setValue(_generation->generation());
	_ui->stv->setScoreTable(_generation->tournament().scoreTable());
}

/***********************************************/
void GenerationView::selectionChanged(pPlayer currplayer)
{
	if(!_grid)
	{
		qWarning() << "No _grid set";
		return;
	}

	if(!currplayer)
	{
		_ui->ggv->clear();
		return;
	}

	auto leftSideRect = _grid->startingLeftSideRect();

	_grid->setState(GridState::Initial); //frees all cells
	_grid->setState(GridState::LeftPlayerPlacing, currplayer); //.-
	currplayer->initGrid(_grid, Side::Left);
	_ui->ggv->drawGrid(_grid, std::get<0>(leftSideRect), std::get<1>(leftSideRect), std::get<2>(leftSideRect), std::get<3>(leftSideRect));

	//indi
	pIndividual indi = std::dynamic_pointer_cast<Individual>(currplayer);
	AttackPriorities aps;

	if(!indi)
	{
		qWarning() << "Cant cast to indi";
		return;
	}

	aps = indi->attackPriorities();
	_ui->tw->clearContents();

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			auto item = new QTableWidgetItem(QString::number(aps.at(static_cast<UnitType>(i)).at(static_cast<UnitType>(j)).value()));

			_ui->tw->setItem(i, j, item);
		}
	}
}

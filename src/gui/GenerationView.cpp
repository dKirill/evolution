/*--------------------------------------------------------------------------*/
#include "evolution/Generation.h"
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
	_grid->setState(GridState::LeftPlayerPlacing, currplayer); //facepalm //.-
	currplayer->initGrid(_grid, Side::Left);
	_ui->ggv->drawGrid(_grid, std::get<0>(leftSideRect), std::get<1>(leftSideRect), std::get<2>(leftSideRect), std::get<3>(leftSideRect));
}

/*--------------------------------------------------------------------------*/
#include "game/Player.h"
#include "game/Score.h"
#include "game/ScoreTable.h"
#include "gui/ScoreTableView.h"
#include "ui_ScoreTableView.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
const QChar nameIdDelim = '.';

/***********************************************/
/***********************************************/
ScoreTableView::ScoreTableView(QWidget* parent) : QWidget(parent), _ui(new Ui::ScoreTableView)
{
	_ui->setupUi(this);
	_ui->tw->setColumnCount(4);
	_ui->tw->setHorizontalHeaderLabels(QStringList() << "Name" << "Wins" << "Ties" << "Loses");

	connect(_ui->tw, &QTableWidget::itemSelectionChanged, this, &ScoreTableView::onSelectionChange);
}

/***********************************************/
ScoreTableView::~ScoreTableView()
{
	delete _ui;
}

/***********************************************/
void ScoreTableView::dropScoreTable()
{
	_stable.reset();
	update();
}

/***********************************************/
void ScoreTableView::setScoreTable(pScoreTable stable)
{
	_stable = stable;
	_stable->setOnAnyChangeCallback([this]() { this->update(); });
	update();
}

/***********************************************/
void ScoreTableView::update()
{
	qDebug() << "ScoreTableView update";
	_ui->tw->clearContents();

	if(!_stable)
	{
		qWarning() << "No update without _stable";
		return;
	}

	Scores setscores = _stable->scores();
	std::vector<pScore> scores{std::begin(setscores), std::end(setscores)};
	int currrow = 0;
	auto sortfunct = [](pScore lscore, pScore rscore)
	{
		if(lscore->wins() > rscore->wins())
			return true;
		else if(lscore->wins() < rscore->wins())
			return false;

		if(lscore->ties() > rscore->ties())
			return true;
		else if(lscore->ties() < rscore->ties())
			return false;

		if(lscore->loses() < rscore->loses())
			return true;
		else
			return false;

		THROW("Error comparing scores");
	};

	std::sort(std::begin(scores), std::end(scores), sortfunct);
	_ui->tw->setRowCount(scores.size());

	for(const auto& sref : scores)
	{
		auto iname = new QTableWidgetItem(sref->player()->name() + nameIdDelim + QString::number(sref->player()->id()));
		auto iwins = new QTableWidgetItem(QString::number(sref->wins()));
		auto ities = new QTableWidgetItem(QString::number(sref->ties()));
		auto iloses = new QTableWidgetItem(QString::number(sref->loses()));

		_ui->tw->setItem(currrow, 0, iname);
		_ui->tw->setItem(currrow, 1, iwins);
		_ui->tw->setItem(currrow, 2, ities);
		_ui->tw->setItem(currrow, 3, iloses);
		++currrow;
	}
}

/***********************************************/
void ScoreTableView::onSelectionChange()
{
	if(_ui->tw->selectedItems().empty())
	{
		qWarning() << "No selection";
		return;
	}

	auto iname = _ui->tw->item(_ui->tw->currentRow(), 0);
	bool ok = false;
	auto id = iname->text().section(nameIdDelim, iname->text().count(nameIdDelim)).toUInt(&ok);
	Scores scores = _stable->scores();
	pPlayer currplayer;

	if(!ok)
	{
		qWarning() << "Can't extract id from name=" << iname->text();
		return;
	}

	auto siter = std::find_if(scores.cbegin(), scores.cend(), [&](Scores::const_reference score) { return id == score->player()->id(); });

	if(siter == scores.end())
		qWarning() << "Couldn't find score by id=" << id;
	else
		currplayer = (*siter)->player();

	emit selectionChanged(currplayer);
}

#ifndef SCORETABLEVIEW_H
#define SCORETABLEVIEW_H

/*--------------------------------------------------------------------------*/
#include <QtWidgets/QWidget>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

namespace Ui {
class ScoreTableView;
}

class ScoreTableView : public QWidget
{
	Q_OBJECT

public:
	explicit ScoreTableView(QWidget* parent = 0);
	~ScoreTableView();

	void dropScoreTable();
	void setScoreTable(pScoreTable stable);
	///redraw stable
	void update();

signals:
	void selectionChanged(pPlayer currselection);

public slots:
	void onSelectionChange();

private:
	pScoreTable _stable;
	Ui::ScoreTableView* _ui;
};

#endif // SCORETABLEVIEW_H

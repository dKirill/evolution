#ifndef GENERATIONVIEW_H
#define GENERATIONVIEW_H

/*--------------------------------------------------------------------------*/
#include <QtWidgets/QWidget>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

namespace Ui {
class GenerationView;
}

class GenerationView : public QWidget
{
	Q_OBJECT

public:
	explicit GenerationView(QWidget* parent = 0);
	~GenerationView();

	void dropGeneration();
	void setGeneration(const pGeneration& generation);
	void update();

public slots:
	void selectionChanged(pPlayer currplayer);

private:
	pGeneration _generation;
	pGrid _grid;
	Ui::GenerationView* _ui;
};

#endif // GENERATIONVIEW_H

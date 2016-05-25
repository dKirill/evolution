/*--------------------------------------------------------------------------*/
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtWidgets/QApplication>
/*--------------------------------------------------------------------------*/
#include "evolution/Generation.h"
#include "evolution/Individual.h"
#include "game/Grid.h"
#include "gui/GenerationView.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	GenerationView view;
	RandEngine reng;
	auto grid = std::make_shared<Grid>(
				"5 10 5 "
				"2 2 0 0 0 1 0 0 3 3 "
				"2 2 0 1 0 0 0 0 3 3 "
				"2 2 0 0 0 0 0 0 3 3 "
				"2 2 0 0 0 0 1 0 3 3 "
				"2 2 0 0 0 1 0 0 3 3 "
				);
	Individuals indis;
	pGeneration gen;
	pGeneration nextgen;

	for(auto i = 0; i < 5; ++i)
		indis.insert(std::make_shared<Individual>(reng));

	gen = std::make_shared<Generation>(grid, indis);
	view.setGeneration(gen);
	nextgen = gen->evolve(reng);
	view.show();

	return app.exec();
}

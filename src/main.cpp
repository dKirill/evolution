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
	GenerationView view2;
	RandEngine reng;
	auto grid = std::make_shared<Grid>(
				"5 6 4 "
				"2 2 1 0 3 3 "
				"2 2 0 0 3 3 "
				"2 2 0 0 3 3 "
				"2 2 0 0 3 3 "
				);
	Individuals indis;
	pGeneration gen;
	pGeneration nextgen;
	pGeneration nextgen2;

	for(auto i = 0; i < 5; ++i)
		indis.insert(std::make_shared<Individual>(reng));

	gen = std::make_shared<Generation>(grid, indis);
	nextgen2 = nextgen = gen;

	for(int i = 0; i < 30; ++i)
	{
		nextgen = nextgen2;
		nextgen2 = nextgen->evolve(reng);
	}

	view.setGeneration(gen);
	view2.setGeneration(nextgen);
	view.show();
	view2.show();

	return app.exec();
}

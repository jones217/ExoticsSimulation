#include <iostream>
#include <conio.h>
#include <memory>
#include <vector>
#include "models.h"
#include "monte_carlo.h"


int main(void)
{

	std::shared_ptr<HestonModels::Heston> h(new HestonModels::Heston);
	h->setRandCorrel(0.3);
	h->setLongRunVar(0.1);
	h->setMeanReversion(0.1);
	h->setVolVol(0.00000000001);
	h->setDrift(0.1);
	h->setSpot(110);
	h->setInitialVol(0.0000000001);
	// Black Model Set Up
	std::shared_ptr<BlackScholesModels::BlackScholes> b(new BlackScholesModels::BlackScholes);
	b->setDrift(0.1);
	b->setSpot(110);
	b->setInitialVol(0.000000001);

	// Monte Carlo Engine set up with chosen model
	//std::shared_ptr<MonteCarlo::cMC<HestonModels::Heston>> mc(new MonteCarlo::cMC < HestonModels::Heston >(h));
	std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC<BlackScholesModels::BlackScholes>);
	mc->setModel(b);

	//std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC < BlackScholesModels::BlackScholes >(b));
	std::vector <std::string> dates;
	dates.push_back("20181107");
	mc->addDates(dates);
	mc->setNumPaths(2000);

	// Run Monte Carlo Engine - save paths to class member "paths"
	mc->generatePaths();

	// Simple evaluation of ATM euro call
	mc->evaluatePaths();
	std::cout << mc->t0MTM() << std::endl;
	_getch();

	// Print paths
	/*
	for (size_t j = 0; j < mc->paths.size(); ++j)
	{
		for (size_t i = 0; i < mc->path.size(); ++i)
			std::cout << mc->path[i] << std::endl;
	}
	

	_getch();
	*/
}
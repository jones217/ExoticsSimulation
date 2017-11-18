#include <iostream>
#include <conio.h>
#include <memory>
#include <vector>
#include "models.h"
#include "monte_carlo.h"
#include "payoffs.h"
#include "trade.h"


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
	b->setInitialVol(0.1);

	// Set up Euro Option
	std::shared_ptr<Vanilla::EuropeanOption> vanillaOption(new Vanilla::EuropeanOption);
	vanillaOption->strike(100.);
	vanillaOption->callPut("Call");
	vanillaOption->maturity("20191111");
	std::shared_ptr<Trade::Trade> vOpt(new Trade::Trade());
	vOpt->setTrade(vanillaOption);

	// Set up Single Barrier
	std::shared_ptr<Barrier::SingleBarrier> singleBarrier(new Barrier::SingleBarrier);
	singleBarrier->strike(100.);
	singleBarrier->callPut("Call");
	singleBarrier->barrierLevel(122.);
	singleBarrier->maturity("20191111");
	std::shared_ptr<Trade::Trade> sBarr(new Trade::Trade());
	sBarr->setTrade(singleBarrier);

	// Set up OneTouch
	std::shared_ptr<Barrier::OneTouch> oneTouch(new Barrier::OneTouch);
	oneTouch->buySell("Buy");
	oneTouch->barrierLevel(122.);
	oneTouch->maturity("20191111");
	std::shared_ptr<Trade::Trade> oTouch(new Trade::Trade());
	oTouch->setTrade(oneTouch);

	// Monte Carlo Engine set up with chosen model
	std::shared_ptr<MonteCarlo::cMC<HestonModels::Heston>> mc(new MonteCarlo::cMC < HestonModels::Heston >(h));
	//std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC<BlackScholesModels::BlackScholes>);
	mc->setModel(h);
	mc->addTrade(vOpt);
	mc->addTrade(sBarr);
	mc->addTrade(oTouch);

	//std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC < BlackScholesModels::BlackScholes >(b));
	std::vector <std::string> dates;
	dates.push_back("20181107");
	dates.push_back("20281107");
	mc->addDates(dates);
	mc->setNumPaths(2000);

	// Run Monte Carlo Engine - save paths to class member "paths"
	mc->generatePaths();

	// Simple evaluation of T0 of trades in portfolio
	mc->evaluatePaths();
	std::cout << mc->t0MTM() << std::endl;
	_getch();
}
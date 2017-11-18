#include <iostream>
#include <conio.h>
#include <memory>
#include <vector>
#include "models.h"
#include "monte_carlo.h"
#include "payoffs.h"
#include "trade.h"
#include "asset_mapping.h"
#include "portfolio.h"


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
	std::shared_ptr<FX::Vanilla::EuropeanOption> vanillaOption(new FX::Vanilla::EuropeanOption);
	vanillaOption->strike(100.);
	vanillaOption->callPut("Call");
	vanillaOption->maturity("20201111");
	vanillaOption->ccyPair("EURUSD");
	vanillaOption->payCcy("EUR");
	std::shared_ptr<Trade::Trade> vOpt(new Trade::Trade());
	vOpt->setTrade(vanillaOption);

	// Set up Single Barrier
	std::shared_ptr<FX::Barrier::SingleBarrier> singleBarrier(new FX::Barrier::SingleBarrier);
	singleBarrier->strike(100.);
	singleBarrier->callPut("Call");
	singleBarrier->barrierLevel(122.);
	singleBarrier->maturity("20191111");
	singleBarrier->ccyPair("USDJPY");
	singleBarrier->payCcy("EUR");
	std::shared_ptr<Trade::Trade> sBarr(new Trade::Trade());
	sBarr->setTrade(singleBarrier);

	// Set up OneTouch
	std::shared_ptr<FX::Barrier::OneTouch> oneTouch(new FX::Barrier::OneTouch);
	oneTouch->buySell("Buy");
	oneTouch->barrierLevel(122.);
	oneTouch->maturity("20191111");
	oneTouch->ccyPair("EURUSD");
	oneTouch->payCcy("USD");
	std::shared_ptr<Trade::Trade> oTouch(new Trade::Trade());
	oTouch->setTrade(oneTouch);

	// Add trades to Portfolio
	Portfolio p;
	p.push_back(vOpt);
	p.push_back(sBarr);
	p.push_back(oTouch);

	PortfolioInspector pI = PortfolioInspector(p);
	std::vector<std::string> assets = pI.assetsForPortfolio();

	// Monte Carlo Engine set up with chosen model
	//std::shared_ptr<MonteCarlo::cMC<HestonModels::Heston>> mc(new MonteCarlo::cMC < HestonModels::Heston >(h));
	std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC<BlackScholesModels::BlackScholes>);
	mc->setModel(b);

	mc->addPortfolio(p);

	std::vector <std::string> dates;
	dates.push_back("20181107");
	dates.push_back("20281107");

	mc->addDates(dates);
	mc->setNumPaths(2000);

	assetSpecs a = assetMapping()[FX_EURUSD];

	// Run Monte Carlo Engine - save paths to class member "paths"
	mc->generatePaths();

	// Simple evaluation of T0 of trades in portfolio
	mc->evaluatePaths();
	std::cout << mc->t0MTM() << std::endl;
	_getch();
}

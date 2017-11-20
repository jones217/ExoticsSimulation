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
#include "universe_simulator.h"

/*
int main(void)
{
	// Set up Euro Option
	std::shared_ptr<FX::Vanilla::EuropeanOption> vanillaOption(new FX::Vanilla::EuropeanOption);
	vanillaOption->strike(1.2);
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
	singleBarrier->barrierLevel(140.);
	singleBarrier->maturity("20191111");
	singleBarrier->ccyPair("USDJPY");
	singleBarrier->payCcy("EUR");
	std::shared_ptr<Trade::Trade> sBarr(new Trade::Trade());
	sBarr->setTrade(singleBarrier);

	// Set up OneTouch
	std::shared_ptr<FX::Barrier::OneTouch> oneTouch(new FX::Barrier::OneTouch);
	oneTouch->buySell("Buy");
	oneTouch->barrierLevel(1.1);
	oneTouch->maturity("20211111");
	oneTouch->ccyPair("EURUSD");
	oneTouch->payCcy("USD");
	std::shared_ptr<Trade::Trade> oTouch(new Trade::Trade());
	oTouch->setTrade(oneTouch);

	// Add trades to Portfolio
	Portfolio p;
	p.push_back(vOpt);
	//p.push_back(sBarr);
	//p.push_back(oTouch);

	std::vector <std::string> dates;
	dates.push_back("20171121");
	dates.push_back("20181107");

	std::shared_ptr<Simulator::UniversalSimulator> s(new Simulator::UniversalSimulator(p));
	s->setNumPaths(20);	
	s->setStartDate("20171120");
	s->setExposureDates(dates);
	s->buildAndSimulateModels();

	Evaluator::UniverseEvaluator i = Evaluator::UniverseEvaluator(s);
	i.evaluate();

	std::cout << i.T0mtm();
	_getch();
}
*/

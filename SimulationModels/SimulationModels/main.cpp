#include <iostream>
#include <conio.h>
#include <memory>
#include <vector>
#include "Models\models.h"
#include "Core\monte_carlo.h"
#include "FXPayoffs\payoffs.h"
#include "TradeWrappers\trade.h"
#include "Models\asset_mapping.h"
#include "TradeWrappers\portfolio.h"
#include "Core\universe_simulator.h"
#include <time.h>

std::shared_ptr<Trade::Trade> vanillaCall(void)
{
	// Set up Euro Option
	std::shared_ptr<FX::Vanilla::EuropeanOption> vanillaOption(new FX::Vanilla::EuropeanOption);
	vanillaOption->strike(1.0);
	vanillaOption->callPut("Call");
	vanillaOption->maturity("20201111");
	vanillaOption->ccyPair("EURUSD");
	vanillaOption->payCcy("EUR");
	std::shared_ptr<Trade::Trade> vOpt(new Trade::Trade());
	vOpt->setTrade(vanillaOption);
	return vOpt;
}

std::shared_ptr<Trade::Trade> singleBarrier(void)
{
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
	return sBarr;
}

std::shared_ptr<Trade::Trade> oneTouch(void)
{
	// Set up OneTouch
	std::shared_ptr<FX::Barrier::OneTouch> oneTouch(new FX::Barrier::OneTouch);
	oneTouch->buySell("Buy");
	oneTouch->barrierLevel(1.1);
	oneTouch->maturity("20211111");
	oneTouch->ccyPair("EURUSD");
	oneTouch->payCcy("USD");
	std::shared_ptr<Trade::Trade> oTouch(new Trade::Trade());
	oTouch->setTrade(oneTouch);
	return oTouch;
}

std::shared_ptr<Portfolio> createPortfolio(void)
{
	std::shared_ptr<Portfolio> p(new Portfolio);
	return p;
}

void addTradesToPortfolio(std::shared_ptr<Portfolio> & portfolio, std::shared_ptr<Trade::Trade> trade)
{
	portfolio->push_back(trade);
}

int main(void)
{
	std::clock_t start = std::clock();
	// Add trades to Portfolio
	Portfolio p;
	p.push_back(vanillaCall());
	p.push_back(singleBarrier());
	p.push_back(oneTouch());

	std::vector <std::string> dates;
	dates.push_back("20171121");
	dates.push_back("20171122");
	dates.push_back("20171123");
	dates.push_back("20180207");
	dates.push_back("20281207");

	std::shared_ptr<Simulator::UniversalSimulator> s(new Simulator::UniversalSimulator(p));
	s->setNumPaths(2000);
	s->setStartDate("20171120");
	s->setExposureDates(dates);
	s->buildAndSimulateModels();

	Evaluator::UniverseEvaluator i = Evaluator::UniverseEvaluator(s);
	i.evaluate();

	std::clock_t timeElapsed = (std::clock() - start);
	unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	std::cout << "Value = " << i.T0mtm() <<std::endl;
	std::cout << "Calculated in " << msElapsed << "ms" << std::endl;
	_getch();
}

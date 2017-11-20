#include "universe_simulator.h"
#include "monte_carlo.h"
#include "asset_mapping.h"
#include "models.h"
#include <map>
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

namespace Simulator
{
	UniversalSimulator::UniversalSimulator()
	{
	}

	UniversalSimulator::UniversalSimulator(Portfolio & portfolio)
	{
		UniversalSimulator::portfolio = portfolio;
		PortfolioInspector pI = PortfolioInspector(portfolio);
		UniversalSimulator::assets = pI.assetsForPortfolio();
		UniversalSimulator::assetMap = assetNameMapping();
		UniversalSimulator::modelMap = assetModelMapping();
		UniversalSimulator::pathResults = std::vector<doubleMat>(10);
	}

	void UniversalSimulator::setNumPaths(double n)
	{
		UniversalSimulator::nPaths = n;
	}

	void UniversalSimulator::setStartDate(std::string d)
	{
		UniversalSimulator::startDate = d;
	}

	void UniversalSimulator::setExposureDates(std::vector <std::string> dateStrs)
	{
		for (auto const& date : dateStrs)
			UniversalSimulator::dates.push_back(date);
	}

	void UniversalSimulator::heston(Assets asset, std::map<std::string, double> specs)
	{
		std::shared_ptr<HestonModels::Heston> h(new HestonModels::Heston);
		h->setRandCorrel(specs["volCorrel"]);
		h->setLongRunVar(specs["lrVar"]);
		h->setMeanReversion(specs["meanReversion"]);
		h->setVolVol(specs["volVol"]);
		h->setDrift(specs["drift"]);
		h->setInitialVol(specs["vol"]);
		h->setSpot(specs["spot"]);
		std::shared_ptr<MonteCarlo::cMC<HestonModels::Heston>> mc(new MonteCarlo::cMC < HestonModels::Heston >(h));
		UniversalSimulator::simulateAndAddToMap(asset, mc);
	}

	void UniversalSimulator::black(Assets asset, std::map<std::string, double> specs)
	{
		std::shared_ptr<BlackScholesModels::BlackScholes> b(new BlackScholesModels::BlackScholes);
		b->setDrift(specs["drift"]);
		b->setSpot(specs["spot"]);
		b->setInitialVol(specs["vol"]);
		std::shared_ptr<MonteCarlo::cMC<BlackScholesModels::BlackScholes>> mc(new MonteCarlo::cMC<BlackScholesModels::BlackScholes>(b));
		UniversalSimulator::simulateAndAddToMap(asset, mc);
	}

	void UniversalSimulator::buildAndSimulateModels(void)
	{
		for (auto const& asset : UniversalSimulator::assets)
		{
			Assets assetName = UniversalSimulator::assetMap[asset];
			assetSpecs specs = UniversalSimulator::modelMap[assetName];
			Models modelType = specs.first;
			std::map<std::string, double> modelSpecs = specs.second;
			switch (modelType){
			case Heston:
				UniversalSimulator::heston(assetName, modelSpecs);
			case BlackScholes:
				UniversalSimulator::black(assetName, modelSpecs);
			}
		}
	}
}


namespace Evaluator
{
	UniverseEvaluator::UniverseEvaluator() 
	{
	}

	UniverseEvaluator::UniverseEvaluator(std::shared_ptr<Simulator::UniversalSimulator> simulator)
	{
		UniverseEvaluator::simulator = simulator;
	}

	void UniverseEvaluator::evaluate(void)
	{
		unsigned nPaths = UniverseEvaluator::simulator->pathResults.begin()->size();
		unsigned nPoints = UniverseEvaluator::simulator->pathResults.begin()->begin()->size();
		std::vector<boost::gregorian::date> dates = UniverseEvaluator::simulator->gDates;
		for (size_t i = 0; i < nPaths; ++i)
		{
			std::vector<double > sumVec(nPoints, 0.0);
			for (auto const& trade : UniverseEvaluator::simulator->portfolio)
			{
				std::vector<double > tmp(nPoints);
				tmp = trade->payoff(
					UniverseEvaluator::simulator->pathResults,
					dates,
					i);
				std::transform(sumVec.begin(), sumVec.end(), tmp.begin(), sumVec.begin(), std::plus<double>());
			}
			UniverseEvaluator::evalPaths.push_back(sumVec);
		}
	}

	double UniverseEvaluator::T0mtm(void)
	{
		double out = 0.;
		for (auto const& path : UniverseEvaluator::evalPaths)
		{
			double tmpSum = 0.;
			for (size_t i = 0; i < path.size(); ++i)
				tmpSum += path[i];
			out += tmpSum;
		}
		return out / (float)UniverseEvaluator::simulator->pathResults.begin()->size();;
	}
}

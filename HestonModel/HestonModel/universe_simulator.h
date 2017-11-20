
#ifndef UNIVERSE_SIMULATOR_H
#define UNIVERSE_SIMULATOR_H
#include "portfolio.h"
#include <vector>
#include "asset_mapping.h"
#include "monte_carlo.h"
#include <memory>
#include <boost\date_time\gregorian\gregorian.hpp>

namespace Simulator
{
	class UniversalSimulator
	{
	public:
		UniversalSimulator();
		UniversalSimulator(Portfolio &);
		void buildAndSimulateModels(void);
		void setNumPaths(double);
		void setStartDate(std::string);
		void setExposureDates(std::vector <std::string>);
		Portfolio portfolio;
		std::vector<doubleMat> pathResults;
		std::vector <boost::gregorian::date> gDates;
	private:
		void heston(Assets, std::map<std::string, double>);
		void black(Assets, std::map<std::string, double>);
		template <typename T>
		void simulateAndAddToMap(Assets, T &);
		std::vector<std::string> assets;
		std::map<std::string, Assets> assetMap;
		std::map<Assets, assetSpecs> modelMap;
		std::vector <std::string> dates;
		double nPaths;
		std::string startDate;
	};

	template <typename T>
	void UniversalSimulator::simulateAndAddToMap(Assets asset, T & mc)
	{
		mc->addPortfolio(UniversalSimulator::portfolio);
		mc->setStartDate(UniversalSimulator::startDate);
		mc->addDates(UniversalSimulator::dates);
		UniversalSimulator::gDates = mc->dates;
		mc->setNumPaths(UniversalSimulator::nPaths);
		mc->generatePaths();
		std::shared_ptr<MonteCarlo::PathEvaluator> pE(new MonteCarlo::PathEvaluator(mc));
		UniversalSimulator::pathResults[asset] = pE->paths;
	}
}

namespace Evaluator
{
	class UniverseEvaluator
	{
	public:
		UniverseEvaluator();
		UniverseEvaluator(std::shared_ptr<Simulator::UniversalSimulator>);
		void evaluate(void);
		double T0mtm(void);
		doubleMat evalPaths;
	private:
		std::shared_ptr<Simulator::UniversalSimulator> simulator;
	};
}

#endif
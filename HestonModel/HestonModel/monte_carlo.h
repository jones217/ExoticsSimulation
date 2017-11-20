
#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include <memory>
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <algorithm>
#include "payoffs.h"
#include "trade.h"
#include "portfolio.h"
#include <string>
//#include "asset_mapping.h"

typedef std::vector<std::vector<double>> doubleMat;

namespace MonteCarlo
{
	template <class  T>
	class cMC
	{
	public:
		cMC();
		cMC(std::shared_ptr<T>);
		void setModel(std::shared_ptr<T>);
		void addPortfolio(Portfolio);
		void generatePath(void);
		void generatePaths(void);
		void addDates(std::vector<std::string>);
		void setNumPaths(int);
		void setStartDate(std::string);
		doubleMat evalPaths;
		doubleMat paths;
		std::vector<boost::gregorian::date> dates;
		unsigned numPaths = 100;
		Portfolio portfolio;
	private:
		std::vector<double > evalPath;
		std::vector<double > path;
		std::shared_ptr<T> t;
		boost::gregorian::date startDate;
	};

	template <class T>
	cMC<T>::cMC(std::shared_ptr<T> y)
	{
		cMC::t = y;
	}

	template <class T>
	cMC<T>::cMC()
	{
	}

	template <class T>
	void cMC<T>::setModel(std::shared_ptr<T> y)
	{
		cMC::t = y;
	}

	template <class T>
	void cMC<T>::setStartDate(std::string date)
	{
		cMC::startDate = boost::gregorian::from_undelimited_string(date);
	}

	template <class T>
	void cMC<T>::addPortfolio(Portfolio p)
	{
		for (auto const& t : p)
		{
			cMC::portfolio.push_back(t);
			std::string maturity = t->maturity();
			cMC::dates.push_back(boost::gregorian::from_undelimited_string(maturity));
			std::sort(cMC::dates.begin(), cMC::dates.end());
			cMC::dates.erase(unique(cMC::dates.begin(), cMC::dates.end()), cMC::dates.end());
		}
	}

	template <class T>
	void cMC<T>::addDates(std::vector<std::string> nDates)
	{
		cMC::dates.push_back(cMC::startDate);
		for (size_t i = 0; i < nDates.size(); ++i)
		{
			cMC::dates.push_back(boost::gregorian::from_undelimited_string(nDates[i]));
		}
		std::sort(cMC::dates.begin(), cMC::dates.end());
		cMC::dates.erase(unique(cMC::dates.begin(), cMC::dates.end()), cMC::dates.end());
	}

	template <class T>
	void cMC<T>::setNumPaths(int nPaths)
	{
		cMC::numPaths = nPaths;
	}

	template <class T>
	void cMC<T>::generatePath(void)
	{
		cMC::path.clear();
		std::vector<double> vals(2);
		vals[0] = t->getSpot();
		vals[1] = t->getInitialVol();
		cMC::path.push_back(vals[0]);
		for (size_t i = 1; i < cMC::dates.size(); ++i)
		{
			double dt = (double)(dates[i] - dates[i - 1]).days()/365.25;
			std::vector<double> W = cMC::t->randomGenerator();
			cMC::t->step(vals, W, dt);
			cMC::path.push_back(vals[0]);
		}
	}

	template <class T>
	void cMC<T>::generatePaths(void)
	{
		for (size_t i = 0; i < cMC::numPaths; ++i)
		{
			cMC::generatePath();
			cMC::paths.push_back(cMC::path);
		}
	}

	class PathEvaluator
	{
	public:
		PathEvaluator();
		template <typename T>
		PathEvaluator(T &);
		void evaluatePath(void);
		void evaluatePaths(void);
		double t0MTM(void);
		doubleMat evalPaths;
		doubleMat paths;
	private:
		std::vector<double> evalPath;
		std::vector<boost::gregorian::date> dates;
		Portfolio portfolio;
		int numPaths;
	};

	template <typename T>
	PathEvaluator::PathEvaluator(T & mc)
	{
		PathEvaluator::dates = mc->dates;
		PathEvaluator::numPaths = mc->numPaths;
		PathEvaluator::portfolio = mc->portfolio;
		PathEvaluator::paths = mc->paths;
	}
}

#endif
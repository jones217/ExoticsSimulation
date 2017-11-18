
#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include <memory>
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <algorithm>

namespace MonteCarlo
{
	template <class  T>
	class cMC
	{
	public:
		cMC();
		cMC(std::shared_ptr<T>);
		void setModel(std::shared_ptr<T>);
		void generatePath(void);
		void generatePaths(void);
		void evaluatePath(void);
		void evaluatePaths(void);
		void addDates(std::vector<std::string>);
		void setNumPaths(int);
		double t0MTM(void);
		std::vector<std::vector<double>> evalPaths;
		std::vector<std::vector<double>> paths;
	private:
		unsigned numPaths=100;
		std::vector<double > matMTM;
		std::vector<double > evalPath;
		std::vector<double > path;
		std::vector<boost::gregorian::date> dates;
		std::shared_ptr<T> t;
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
	void cMC<T>::addDates(std::vector<std::string> nDates)
	{
		cMC::dates.push_back(boost::gregorian::day_clock::local_day());
		for (size_t i = 0; i < nDates.size(); ++i)
		{
			cMC::dates.push_back(boost::gregorian::from_undelimited_string(nDates[i]));
		}
		std::sort(cMC::dates.begin(), cMC::dates.end());
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

	template <class T>
	void cMC<T>::evaluatePath(void)
	{
		float tmp;
		for (size_t i = cMC::evalPath.size() - 1; i > 0; --i)
		{
			if (i == cMC::evalPath.size() - 1)
				tmp = std::max(cMC::evalPath[i] - 100., 0.);
			else
				tmp = 0;
			cMC::evalPath[i] = tmp;
		}
	}

	template <class T>
	void cMC<T>::evaluatePaths(void)
	{
		
		std::vector <std::vector<double> > nArr(cMC::paths.size(), std::vector<double>(cMC::paths[0].size(), 0));
		cMC::evalPaths = nArr;
		for (size_t i = 0; i < cMC::paths.size(); ++i) 
		{
			cMC::evalPath = cMC::paths[i];
			cMC::evaluatePath();
			cMC::evalPaths[i] = cMC::evalPath;
			cMC::matMTM.push_back(evalPath.back());
		}
	}

	template <class T>
	double cMC<T>::t0MTM(void)
	{
		double out = 0.;
		for (size_t i = 0; i < cMC::matMTM.size(); ++i)
		{
			out += cMC::matMTM[0];
		}
		return out / (float)cMC::numPaths;
	}
}

#endif
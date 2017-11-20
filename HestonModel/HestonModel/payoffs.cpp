#include <vector>
#include <algorithm>
#include "payoffs.h"
#include <boost\date_time\gregorian\gregorian.hpp>
#include "asset_mapping.h"
#include <math.h>
#include <map>

double discountFactor(std::vector<double> &rate, std::vector<boost::gregorian::date> &dates, int time)
{
	double factor = 0;
	for (size_t t = 1; t <= time; ++t)
	{
		float dt = (dates[t] - dates[t - 1]).days() / 365.25;
		float r = rate[t - 1];
		factor += dt * r;
	}
	return std::exp(-factor);
}

std::map<std::string, Assets> assetMap = assetNameMapping();

namespace FX
{
	void FXBase::maturity(std::string T)
	{
		FXBase::T = T;
		FXBase::mat = boost::gregorian::from_undelimited_string(T);
	}

	std::vector<std::string> FXBase::getUnderlyings(void)
	{
		FXBase::underlyings.push_back(FXBase::pair);
		FXBase::underlyings.push_back(FXBase::pay);
		return FXBase::underlyings;
	}

	void FXBase::ccyPair(std::string pair)
	{
		FXBase::pair = pair;
	};

	void FXBase::payCcy(std::string pay)
	{
		FXBase::pay = pay;
	};

	namespace Vanilla
	{
		EuropeanOption::EuropeanOption(void)
		{
		};

		void EuropeanOption::strike(float k)
		{
			EuropeanOption::k = k;
		};

		void EuropeanOption::callPut(std::string cp)
		{
			EuropeanOption::cp = cp;
		};

		std::vector<double > EuropeanOption::payoff(std::vector<doubleMat> & paths, std::vector<boost::gregorian::date> dates, int index)
		{
			double tmp;
			Assets ccyPair = assetMap[EuropeanOption::pair];
			Assets payCcy = assetMap[EuropeanOption::pay];
			std::vector<double> spot = paths[ccyPair][index];
			std::vector<double> res(spot.size());
			for (int i = spot.size() - 1; i >= 0; --i)
			{
				if (dates[i] == EuropeanOption::mat)
					tmp = std::max(spot[i] - EuropeanOption::k, 0.) * discountFactor(paths[IR_USD][index], dates, i);
				else
					tmp = 0;
				res[i] = tmp;
			}
			return res;
		}
	}

	namespace Barrier
	{
		SingleBarrier::SingleBarrier(void)
		{
		};

		void SingleBarrier::strike(float k)
		{
			SingleBarrier::k = k;
		};

		void SingleBarrier::barrierLevel(float b)
		{
			SingleBarrier::b = b;
		};

		void SingleBarrier::callPut(std::string cp)
		{
			SingleBarrier::cp = cp;
		};

		std::vector<double > SingleBarrier::payoff(std::vector<doubleMat> & paths, std::vector<boost::gregorian::date>dates, int index)
		{
			double tmp;
			float ko = 1.;
			Assets ccyPair = assetMap[SingleBarrier::pair];
			std::vector<double> spot = paths[ccyPair][index];
			std::vector<double> res(spot.size());
			for (int i = 0; i < spot.size(); ++i)
			{
				if (spot[i] >= SingleBarrier::b)
					ko = 0;
				if (dates[i] == SingleBarrier::mat)
					tmp = ko * (std::max(spot[i] - SingleBarrier::k, 0.)) * discountFactor(paths[IR_USD][index], dates, i);
				else
					tmp = 0;
				res[i] = tmp;
			}
			return res;
		}

		OneTouch::OneTouch(void)
		{
		};

		void OneTouch::barrierLevel(float b)
		{
			OneTouch::b = b;
		};

		void OneTouch::buySell(std::string bs)
		{
			OneTouch::bs = bs;
		};


		std::vector<double > OneTouch::payoff(std::vector<doubleMat> & paths, std::vector<boost::gregorian::date> dates, int index)
		{
			double tmp;
			float touched = 0.;
			Assets ccyPair = assetMap[OneTouch::pair];
			std::vector<double> spot = paths[ccyPair][index];
			std::vector<double> res(spot.size());
			for (int i = 0; i < spot.size(); ++i)
			{
				if (dates[i] <= OneTouch::mat)
				{
					if (spot[i] >= OneTouch::b)
						touched = 1.;
				}
				if (dates[i] == OneTouch::mat)
					res[i] = touched * discountFactor(paths[IR_USD][index], dates, i);
				else
					res[i] = 0.;
			}
			return res;
		}


	}
}



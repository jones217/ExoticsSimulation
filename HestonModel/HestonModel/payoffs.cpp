#include <vector>
#include <algorithm>
#include "payoffs.h"
#include <boost\date_time\gregorian\gregorian.hpp>

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

	void EuropeanOption::maturity(std::string T)
	{
		EuropeanOption::T = T;
		EuropeanOption::mat = boost::gregorian::from_undelimited_string(T);
	};

	std::vector<double > EuropeanOption::payoff(std::vector<double > evalPath, std::vector<boost::gregorian::date> dates)
	{
		double tmp;
		for (int i = evalPath.size() - 1; i > 0; --i)
		{
			if (dates[i] == EuropeanOption::mat)
				tmp = std::max(evalPath[i] - EuropeanOption::k, 0.);
			else
				tmp = 0;
			evalPath[i] = tmp;
		}
		return evalPath;
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

	void SingleBarrier::maturity(std::string T)
	{
		SingleBarrier::T = T;
		SingleBarrier::mat = boost::gregorian::from_undelimited_string(T);
	};

	std::vector<double > SingleBarrier::payoff(std::vector<double > evalPath, std::vector<boost::gregorian::date> dates)
	{
		double tmp;
		double ko = 1;
		for (int i = evalPath.size() - 1; i > 0; --i)
		{
			if (evalPath[i] >= SingleBarrier::b)
				ko = 0;
			if (dates[i] == SingleBarrier::mat)
				tmp = ko * (std::max(evalPath[i] - SingleBarrier::k, 0.));
			else
				tmp = 0;
			evalPath[i] = tmp;
		}
		return evalPath;
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

	void OneTouch::maturity(std::string T)
	{
		OneTouch::T = T;
		OneTouch::mat = boost::gregorian::from_undelimited_string(T);
	};

	std::vector<double > OneTouch::payoff(std::vector<double > evalPath, std::vector<boost::gregorian::date> dates)
	{
		double touched = 0.;
		for (int i = evalPath.size() - 1; i >= 0; --i)
		{
			if (dates[i] <= OneTouch::mat)
			{
				if (evalPath[i] >= OneTouch::b)
					touched = 1.;
			}
			if (dates[i] == OneTouch::mat)
				evalPath[i] = touched;
			else
				evalPath[i] = 0.;
		}
		return evalPath;
	}


}
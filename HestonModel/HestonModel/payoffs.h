
#ifndef PAYOFFS_H
#define PAYOFFS_H
#include <vector>
#include <memory>
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

enum CallPut
{
	Call,
	Put
};

namespace Vanilla
{
	class EuropeanOption
	{
	public:
		EuropeanOption();
		std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
		void strike(float);
		void callPut(std::string);
		void maturity(std::string);
		std::string maturity(void) { return T; }
	private:
		double k;
		std::string cp;
		std::string T;
		boost::gregorian::date mat;
	};

}

namespace Barrier
{
	class SingleBarrier
	{
	public:
		SingleBarrier();
		std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
		void strike(float);
		void barrierLevel(float);
		void callPut(std::string);
		void maturity(std::string);
		std::string maturity(void) { return T; }
	private:
		double k, b;
		std::string cp;
		std::string T;
		boost::gregorian::date mat;
	};

	class OneTouch
	{
	public:
		OneTouch();
		std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
		void barrierLevel(float);
		void buySell(std::string);
		void maturity(std::string);
		std::string maturity(void) { return T; }
	private:
		double b;
		std::string bs;
		std::string T;
		boost::gregorian::date mat;
	};

}

#endif
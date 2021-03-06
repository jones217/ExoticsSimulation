
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

class BaseTrade
{
public:
	virtual std::vector<std::string> getUnderlyings(void) { return std::vector<std::string>({""});
}
	std::string maturity(void) { return T; };
	std::string assetClass;
	std::vector<std::string> underlyings;
	boost::gregorian::date mat;
	std::string T;
};

namespace FX
{
	class FXBase : public BaseTrade
	{
	public:
		void maturity(std::string);
		void ccyPair(std::string);
		void payCcy(std::string);
		std::vector<std::string> getUnderlyings(void);
		std::string maturity(void) { return T; }
		std::string pair, pay, assetClass="FX";
		boost::gregorian::date mat;
		std::string T;
	};

	namespace Vanilla
	{
		class EuropeanOption: public FXBase
		{
		public:
			EuropeanOption();
			std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
			void strike(float);
			void callPut(std::string);
		private:
			double k;
			std::string cp;
		};
	}

	namespace Barrier
	{
		class SingleBarrier : public FXBase
		{
		public:
			SingleBarrier();
			std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
			void strike(float);
			void barrierLevel(float);
			void callPut(std::string);
		private:
			double k, b;
			std::string cp;
		};

		class OneTouch : public FXBase
		{
		public:
			OneTouch();
			std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
			void barrierLevel(float);
			void buySell(std::string);
		private:
			double b;
			std::string bs;
		};

	}
}

#endif
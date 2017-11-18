
#ifndef TRADE_H
#define TRADE_H
#include <vector>
#include <memory>
#include "payoffs.h"
#include <boost\variant.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>

typedef boost::variant<
	std::shared_ptr<Vanilla::EuropeanOption>,
	std::shared_ptr<Barrier::SingleBarrier>,
	std::shared_ptr<Barrier::OneTouch>
> tradeTypes;

namespace Trade
{
	class CalculatePayoff
		: public boost::static_visitor<std::vector<double>>
	{
	public:
		CalculatePayoff(std::vector<double > path, std::vector<boost::gregorian::date> date) : path(path), date(date) { }

		template <typename T>
		std::vector<double > operator()(T & trade) const
		{
			return trade->payoff(path, date);
		}
	private:
		std::vector<double > path;
		std::vector<boost::gregorian::date> date;
	};

	class GatherMaturity
		: public boost::static_visitor<std::string>
	{
	public:
		GatherMaturity() {};

		template <typename T>
		std::string operator()(T & trade) const
		{
			return trade->maturity();
		}
	};

	class Trade
	{
	public:
		Trade();
		void setTrade(std::shared_ptr<Vanilla::EuropeanOption>);
		void setTrade(std::shared_ptr<Barrier::SingleBarrier>);
		void setTrade(std::shared_ptr<Barrier::OneTouch>);
		std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
		std::string maturity();
	private:
		tradeTypes t;
	};

	Trade::Trade()
	{
	}

	void Trade::setTrade(std::shared_ptr<Vanilla::EuropeanOption> t)
	{
		Trade::t = t;
	}

	void Trade::setTrade(std::shared_ptr<Barrier::SingleBarrier> t)
	{
		Trade::t = t;
	}

	void Trade::setTrade(std::shared_ptr<Barrier::OneTouch> t)
	{
		Trade::t = t;
	}

	std::vector<double > Trade::payoff(std::vector<double > p, std::vector<boost::gregorian::date> d)
	{
		return boost::apply_visitor(CalculatePayoff(p, d), Trade::t);
	}

	std::string Trade::maturity()
	{
		return boost::apply_visitor(GatherMaturity(), Trade::t);
	}
}

#endif
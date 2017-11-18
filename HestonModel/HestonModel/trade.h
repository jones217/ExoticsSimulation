
#ifndef TRADE_H
#define TRADE_H
#include <vector>
#include <memory>
#include "payoffs.h"
#include <boost\variant.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>

typedef boost::variant<
	std::shared_ptr<FX::Vanilla::EuropeanOption>,
	std::shared_ptr<FX::Barrier::SingleBarrier>,
	std::shared_ptr<FX::Barrier::OneTouch>
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

	class GatherAssetClass
		: public boost::static_visitor<std::string>
	{
	public:
		GatherAssetClass() {};

		template <typename T>
		std::string operator()(T & trade) const
		{
			return trade->assetClass;
		}
	};

	class GatherUnderlyings
		: public boost::static_visitor<std::vector<std::string>>
	{
	public:
		GatherUnderlyings() {};

		template <typename T>
		std::vector<std::string> operator()(T & trade) const
		{
			return trade->getUnderlyings();
		}
	};

	class Trade
	{
	public:
		Trade();
		void setTrade(std::shared_ptr<FX::Vanilla::EuropeanOption>);
		void setTrade(std::shared_ptr<FX::Barrier::SingleBarrier>);
		void setTrade(std::shared_ptr<FX::Barrier::OneTouch>);
		std::vector<double > payoff(std::vector<double >, std::vector<boost::gregorian::date>);
		std::string maturity();
		std::string assetClass();
		std::vector<std::string> underlyings();
	private:
		tradeTypes t;
	};
}

#endif
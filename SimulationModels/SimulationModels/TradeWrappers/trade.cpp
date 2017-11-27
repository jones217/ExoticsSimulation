#include <vector>
#include <memory>
#include <boost\variant.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "..\TradeWrappers\trade.h"
#include "..\FXPayoffs\payoffs.h"

namespace Trade
{
	Trade::Trade()
	{
	}

	void Trade::setTrade(std::shared_ptr<FX::Vanilla::EuropeanOption> t)
	{
		Trade::t = t;
	}

	void Trade::setTrade(std::shared_ptr<FX::Barrier::SingleBarrier> t)
	{
		Trade::t = t;
	}

	void Trade::setTrade(std::shared_ptr<FX::Barrier::OneTouch> t)
	{
		Trade::t = t;
	}

	std::vector<double > Trade::payoff(std::vector<doubleMat> & p, std::vector<boost::gregorian::date> d, int i)
	{
		return boost::apply_visitor(CalculatePayoff(p, d, i), Trade::t);
	}

	std::string Trade::maturity()
	{
		return boost::apply_visitor(GatherMaturity(), Trade::t);
	}

	std::string Trade::assetClass()
	{
		return boost::apply_visitor(GatherAssetClass(), Trade::t);
	}

	std::vector<std::string> Trade::underlyings()
	{
		return boost::apply_visitor(GatherUnderlyings(), Trade::t);
	}
}
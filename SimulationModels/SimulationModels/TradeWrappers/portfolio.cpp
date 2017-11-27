
#include <algorithm>
#include "..\TradeWrappers\portfolio.h"

PortfolioInspector::PortfolioInspector()
{
}

PortfolioInspector::PortfolioInspector(Portfolio p)
{
	PortfolioInspector::portfolio = p;
}

std::vector<std::string> PortfolioInspector::assetsForPortfolio(void)
{
	std::vector<std::string> assets;
	for (auto const& t : PortfolioInspector::portfolio)
	{
		std::vector<std::string> tmp = t->underlyings();
		std::vector<std::string> tUnderlyings;
		for (auto const& asset : tmp)
		{
			if (asset.size() == 3)
				tUnderlyings.push_back(asset);
			else if (asset.size() == 6)
			{
				tUnderlyings.push_back(asset);
				tUnderlyings.push_back(asset.substr(0, 3));
				tUnderlyings.push_back(asset.substr(3, 6));
			}
		}

		assets.insert(assets.end(), tUnderlyings.begin(), tUnderlyings.end());
	}
	std::sort(assets.begin(), assets.end());
	assets.erase(unique(assets.begin(), assets.end()), assets.end());
	return assets;
}

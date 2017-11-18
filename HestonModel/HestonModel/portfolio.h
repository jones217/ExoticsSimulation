
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <vector>
#include <memory>
#include "trade.h"

typedef std::vector<std::shared_ptr<Trade::Trade>> Portfolio;

class PortfolioInspector
{
public:
	PortfolioInspector();
	PortfolioInspector(Portfolio);
	Portfolio portfolio;
	std::vector<std::string> assetsForPortfolio(void);
};

#endif

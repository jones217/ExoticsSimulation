#include "universe_simulator.h"
#include "monte_carlo.h"
#include "asset_mapping.h"
#include "portfolio.h"

namespace Simulator
{
	UniversalSimulator::UniversalSimulator(Portfolio portfolio)
	{
		PortfolioInspector pI = PortfolioInspector(portfolio);
		UniversalSimulator::assets = pI.assetsForPortfolio();
		std::map<std::string, Assets> assetMap = assetNameMapping();
	}
}
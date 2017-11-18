
#ifndef ASSET_MAPPING_H
#define ASSET_MAPPING_H
#include <utility>
#include <map>
#include <list>

enum Assets{
	FX_EURUSD,
	FX_USDJPY,
	IR_USD,
	IR_EUR,
	IR_JPY,
};

enum Models {
	Heston,
	BlackScholes,
};

typedef std::pair<Models, std::list<double>> assetSpecs;

std::map<Assets, assetSpecs> assetMapping(void)
{
	std::map<Assets, assetSpecs> assetMap;

	// Asset -> [Model, (Volatility, Drift)]
	
	//FX
	assetMap[FX_EURUSD] = assetSpecs(Heston, { 0.12, 0.01 });
	assetMap[FX_USDJPY] = assetSpecs(Heston, { 0.08, 0.02 });

	//Rates
	assetMap[IR_USD] = assetSpecs(BlackScholes, { 0.005, 0.01 });
	assetMap[IR_EUR] = assetSpecs(BlackScholes, { 0.006, 0.02 });
	assetMap[IR_JPY] = assetSpecs(BlackScholes, { 0.01, 0.03 });

	return assetMap;
}

#endif

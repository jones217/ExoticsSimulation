#include "asset_mapping.h"


std::map<std::string, Assets> assetNameMapping(void)
{
	std::map<std::string, Assets> assetNameMap;
	assetNameMap["EURUSD"] = FX_EURUSD;
	assetNameMap["USDJPY"] = FX_USDJPY;
	assetNameMap["USD"] = IR_USD;
	assetNameMap["EUR"] = IR_EUR;
	assetNameMap["JPY"] = IR_JPY;
	return assetNameMap;
}

std::map<Assets, assetSpecs> assetModelMapping(void)
{
	std::map<Assets, assetSpecs> assetMap;

	// Asset -> [Model, (Volatility, Drift)]

	//FX
	assetMap[FX_EURUSD] = assetSpecs(Heston, {
		{"vol", 0.01 / std::sqrt(252)}, {"drift", 0.01}, {"spot", 1.08},
		{"volVol", 0.00001 / std::sqrt(252) }, {"meanReversion", 0.001}, {"lrVar", 0.01 / std::sqrt(252) },
		{"volCorrel", 0.3}
	});
	assetMap[FX_USDJPY] = assetSpecs(Heston, {
		{ "vol", 0.008 / std::sqrt(252) }, { "drift", 0.02 }, { "spot", 121.0 },
		{ "volVol", 0.0002 / std::sqrt(252) }, { "meanReversion", 0.05 }, { "lrVar", 0.01 / std::sqrt(252) },
		{ "volCorrel", 0.1 }
	});

	//Rates
	assetMap[IR_USD] = assetSpecs(BlackScholes, {
		{ "vol", 0.0008 / std::sqrt(252) },{ "drift", 0.00 },{ "spot", 0.005 }
	});
	assetMap[IR_EUR] = assetSpecs(BlackScholes, {
		{ "vol", 0.0006 / std::sqrt(252) },{ "drift", 0.01 },{ "spot", 0.0025 }
	});
	assetMap[IR_JPY] = assetSpecs(BlackScholes, {
		{ "vol", 0.0002 / std::sqrt(252) },{ "drift", 0.002 },{ "spot", 0.01 }
	});

	return assetMap;
}
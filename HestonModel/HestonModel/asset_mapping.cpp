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
	assetMap[FX_EURUSD] = assetSpecs(Heston, { 0.12, 0.01 });
	assetMap[FX_USDJPY] = assetSpecs(Heston, { 0.08, 0.02 });

	//Rates
	assetMap[IR_USD] = assetSpecs(BlackScholes, { 0.005, 0.01 });
	assetMap[IR_EUR] = assetSpecs(BlackScholes, { 0.006, 0.02 });
	assetMap[IR_JPY] = assetSpecs(BlackScholes, { 0.01, 0.03 });

	return assetMap;
}
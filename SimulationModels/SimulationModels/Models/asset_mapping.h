
#ifndef ASSET_MAPPING_H
#define ASSET_MAPPING_H
#include <utility>
#include <map>
#include <list>
#include <string>

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

typedef std::pair<Models, std::map<std::string, double>> assetSpecs;

std::map<std::string, Assets> assetNameMapping(void);
std::map<Assets, assetSpecs> assetModelMapping(void);

#endif

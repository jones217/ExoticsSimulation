
#ifndef UNIVERSE_SIMULATOR_H
#define UNIVERSE_SIMULATOR_H
#include "portfolio.h"
#include <vector>
#include "asset_mapping.h"

namespace Simulator
{
	class UniversalSimulator
	{
	public:
		UniversalSimulator();
		UniversalSimulator(Portfolio);
		void simulate(void);
	private:
		std::vector<Models> modelList;
		std::vector<std::string> assets;
	};
}

#endif
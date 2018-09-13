// SimulationModelGenerator.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "simulation_library.h"
#include <iostream>
#include <conio.h>
#include <memory>
#include <vector>
#include <Models\models.h>
#include <Core\monte_carlo.h>
#include <FXPayoffs\payoffs.h>
#include <TradeWrappers\trade.h>
#include <Models\asset_mapping.h>
#include <TradeWrappers\portfolio.h>
#include <Core\universe_simulator.h>
#include <time.h>



extern"C" 
{
	Trade::Trade* vanillaCall(void)
	{
		// Set up Euro Option
		std::shared_ptr<FX::Vanilla::EuropeanOption> vanillaOption(new FX::Vanilla::EuropeanOption());
		vanillaOption->strike(1.0);
		vanillaOption->callPut("Call");
		vanillaOption->maturity("20201111");
		vanillaOption->ccyPair("EURUSD");
		vanillaOption->payCcy("EUR");
		Trade::Trade *vOpt(new Trade::Trade());
		vOpt->setTrade(vanillaOption);
		return vOpt;
	}

	int test(float i)
	{
		float * n(new float(i));
		int k = int(&n);
		return k;
	}
	float *testT(int i )
	{
		float * a(new float(i));
		return a;
	}
}

/*

//std::shared_ptr<Trade::Trade> tradeWrapper(


extern "C" float vanillaCall2(void)
{
	return 2.0;
}
*/
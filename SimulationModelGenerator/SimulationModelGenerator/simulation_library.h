// MathLibrary.h - Contains declaration of Function class  
#pragma once  

#ifdef SIMULATION_LIBRARY_EXPORTS  
#define SIMULATION_LIBRARY_API __declspec(dllexport)   
#else  
#define SIMULATION_LIBRARY_API __declspec(dllimport)   
#endif  
#include <memory>
#include <TradeWrappers\trade.h>
#include <FXPayoffs\payoffs.h>

typedef  std::shared_ptr<Trade::Trade> TradeWrapperPtr;

extern"C"
{
	//SIMULATION_LIBRARY_API std::shared_ptr<Trade::Trade> vanillaCall(void);
	SIMULATION_LIBRARY_API Trade::Trade *vanillaCall(void);
	SIMULATION_LIBRARY_API int test(float);
	SIMULATION_LIBRARY_API float* testT(int);
}
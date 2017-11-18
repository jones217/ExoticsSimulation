
#ifndef MODELS_H
#define MODELS_H
#include <vector>
#include "model_utils.h"
#include <boost\random\normal_distribution.hpp>
#include <boost\random\mersenne_twister.hpp>
#include <boost\random\variate_generator.hpp>

enum ModelType
{
	Heston,
	BlackScholes
};


namespace HestonModels
{
	class Heston : public ModelUtils::BaseModel
	{
	public:
		Heston();
		~Heston();
		void setRandCorrel(float);
		void setLongRunVar(float);
		void setMeanReversion(float);
		void setVolVol(float);
		std::vector<double> randomGenerator(void);
		void step(std::vector<double> &, std::vector<double>, float);
	private:
		float lrVar, mrRate, volVol, dt, rnCorrel;
		float dVt(float, float, float);
		float dSt(float, float, float, float);
		std::vector < std::vector < double > > randomNumbers;
		typedef boost::mt19937                     ENG;
		typedef boost::normal_distribution<double> DIST;
		typedef boost::variate_generator<ENG, DIST> GEN;
		ENG eng;
		DIST dist;
		GEN gen;
	};
}

namespace BlackScholesModels
{
	class BlackScholes : public ModelUtils::BaseModel
	{
	public:
		BlackScholes();
		~BlackScholes();
		std::vector<double> randomGenerator(void);
		void step(std::vector<double> &, std::vector<double>, float);
	private:
		typedef boost::mt19937                     ENG;
		typedef boost::normal_distribution<double> DIST;
		typedef boost::variate_generator<ENG, DIST> GEN;
		ENG eng;
		DIST dist;
		GEN gen;
	};
}

#endif
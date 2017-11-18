#include <vector>
#include <math.h>
#include "model_utils.h"
#include <memory>
#include "models.h"

namespace HestonModels
{

	Heston::Heston(void) : dist(0, 1), gen(eng, dist)
	{}

	Heston::~Heston(void)
	{
	}

	void Heston::setRandCorrel(float correl)
	{
		Heston::rnCorrel = correl;
	}

	void Heston::setLongRunVar(float lrVar)
	{
		Heston::lrVar = lrVar;
	}

	void Heston::setMeanReversion(float mrRate)
	{
		Heston::mrRate = mrRate;
	}

	void Heston::setVolVol(float volVol)
	{
		Heston::volVol = volVol;
	}

	std::vector<double> Heston::randomGenerator(void)
	{
		return ModelUtils::correlatedRandomPair(Heston::rnCorrel, Heston::gen);
	}

	void Heston::step(std::vector<double> &vals, std::vector<double> W, float dt=0.1)
	{
		float vT = Heston::dVt(vals[1], W[1], dt);
		vals[1] = vals[1] + vT;
		float sT = Heston::dSt(vals[0], vals[1], W[0], dt);
		vals[0] = vals[0] + sT;
	}

	float Heston::dVt(float vt, float W_2, float dt)
	{
		return ((Heston::mrRate * (Heston::lrVar - vt) * dt) + (Heston::volVol * sqrt(vt) * W_2));
	}

	float Heston::dSt(float St, float Vt, float W_1, float dt)
	{
		return St * ((Heston::drift * dt) + (sqrt(Vt) * W_1));
	}
}

namespace BlackScholesModels
{
	BlackScholes::BlackScholes() : dist(0, 1), gen(eng, dist)
	{}

	BlackScholes::~BlackScholes()
	{
	}

	std::vector<double> BlackScholes::randomGenerator(void)
	{
		return ModelUtils::randomGenerator(BlackScholes::gen);
	}


	void BlackScholes::step(std::vector<double> &vals, std::vector<double> W, float dt = 0.1)
	{
		float sT = vals[0] * ((BlackScholes::drift * dt) + (sqrt(BlackScholes::vol) * W[0]));
		vals[0] = vals[0] + sT;
	}

}
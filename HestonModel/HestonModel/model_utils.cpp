#include "model_utils.h"
#include <boost\random\normal_distribution.hpp>
#include <boost\random\mersenne_twister.hpp>
#include <boost\random\variate_generator.hpp>
#include <vector>
#include <math.h>
#include "matrix_alg.h"


namespace ModelUtils
{

	void BaseModel::setDrift(float drift)
	{
		BaseModel::drift = drift;
	}

	void BaseModel::setSpot(float spot)
	{
		BaseModel::spot = spot;
	}

	float BaseModel::getSpot(void)
	{
		return BaseModel::spot;
	}

	void BaseModel::setInitialVol(float vol)
	{
		BaseModel::vol = vol;
	}

	float BaseModel::getInitialVol(void)
	{
		return BaseModel::vol;
	}

	std::vector<double> randomGenerator(boost::variate_generator<boost::mt19937, boost::normal_distribution<> > & generator)
	{
		std::vector<double> res;
		res.push_back(gen_normal_3(generator));
		return res;
	}

	std::vector<double> correlatedRandomPair(float correl, boost::variate_generator<boost::mt19937, boost::normal_distribution<> > & generator)
	{
		std::vector < std::vector <double> > res;
		std::vector <std::vector<double> > correlMat(2, std::vector<double>(2, 0));

		correlMat[0][0] = 1;
		correlMat[1][0] = 0;
		correlMat[0][1] = correl;
		correlMat[1][1] = sqrt(1 - pow(correl, 2));

		std::vector<double> newPair(2), correlPair(2);
		gen_normal_3(generator, newPair);
		std::vector< std::vector < double > > newMat(1);
		newMat[0] = newPair;
		std::vector< std::vector < double > > correlNum = MatrixAlg::MatMult(newMat, correlMat);

		return correlNum[0];
	}

	template<class T>
	double ModelUtils::gen_normal_3(T &generator)
	{
		return generator();
	}

	// generate pair
	template<class T>
	void ModelUtils::gen_normal_3(T &generator,
		std::vector<double> &res)
	{
		res[0] = generator();
		res[1] = generator();
	}
}
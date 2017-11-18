
#ifndef MODEL_UTILS_H
#define MODEL_UTILS_H
#include <vector>
#include <boost\random\normal_distribution.hpp>
#include <boost\random\mersenne_twister.hpp>
#include <boost\random\variate_generator.hpp>

namespace ModelUtils
{
	class BaseModel
	{
	public:
		virtual void setDrift(float);
		virtual void setSpot(float);
		virtual void setInitialVol(float);
		virtual float getSpot(void);
		virtual float getInitialVol(void);
	protected:
		float spot, vol, drift;
	};

	std::vector<double> randomGenerator(boost::variate_generator<boost::mt19937, boost::normal_distribution<> > & generator);

	std::vector < double > correlatedRandomPair(float, boost::variate_generator<boost::mt19937, boost::normal_distribution<> > &);

	template<class T>
	double gen_normal_3(T &generator);

	// generate pair
	template<class T>
	void gen_normal_3(T &generator,
		std::vector<double> &res);
}

#endif
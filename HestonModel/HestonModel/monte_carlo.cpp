
#include "monte_carlo.h"
#include "portfolio.h"
#include <vector>

namespace MonteCarlo
{
	PathEvaluator::PathEvaluator()
	{
	}

	void PathEvaluator::evaluatePath(void)
	{
		std::vector<double > sumVec(PathEvaluator::evalPath.size(), 0.0);
		for (auto const& trade : PathEvaluator::portfolio)
		{
			std::vector<double > tmp = trade->payoff(PathEvaluator::evalPath, PathEvaluator::dates);
			std::transform(sumVec.begin(), sumVec.end(), tmp.begin(), sumVec.begin(), std::plus<double>());
		}
		PathEvaluator::evalPath = sumVec;
	}

	void PathEvaluator::evaluatePaths(void)
	{

		std::vector <std::vector<double> > nArr(PathEvaluator::paths.size(), std::vector<double>(PathEvaluator::paths[0].size(), 0));
		PathEvaluator::evalPaths = nArr;
		for (size_t i = 0; i < PathEvaluator::paths.size(); ++i)
		{
			PathEvaluator::evalPath = PathEvaluator::paths[i];
			PathEvaluator::evaluatePath();
			PathEvaluator::evalPaths[i] = PathEvaluator::evalPath;
		}
	}

	double PathEvaluator::t0MTM(void)
	{
		double out = 0.;
		for (auto const& path : PathEvaluator::evalPaths)
		{
			double tmpSum = 0.;
			for (size_t i = 0; i < path.size(); ++i)
				tmpSum += path[i];
			out += tmpSum;
		}
		return out / (float)PathEvaluator::numPaths;
	}
	
}
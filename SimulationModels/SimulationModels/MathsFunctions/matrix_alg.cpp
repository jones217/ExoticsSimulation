#include <vector>
#include "..\MathsFunctions\matrix_alg.h"


std::vector<std::vector<double>> MatrixAlg::MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
	int n = A.size();
	int m = A[0].size();
	int p = B[0].size();

	std::vector<double> tmp(p, 0.);
	std::vector <std::vector<double> > AB(n, tmp);

	for (size_t i = 0; i < n; ++i) {
		for (size_t k = 0; k < m; ++k) {
			for (size_t j = 0; j < p; ++j) {
				AB[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return AB;
}

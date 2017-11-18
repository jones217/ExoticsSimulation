#include <vector>
#include "matrix_alg.h"


std::vector<std::vector<double>> MatrixAlg::MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
	int n = A.size();
	int m = A[0].size();
	int p = B[0].size();

	std::vector <std::vector<double> > AB(n, std::vector<double>(p, 0));

	for (int j = 0; j < p; ++j) {
		for (int k = 0; k < m; ++k) {
			for (int i = 0; i < n; ++i) {
				AB[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return AB;
}

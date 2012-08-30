
#include "LinSolver.h"

using namespace std;


int main (void)
{
	//starting at 9:35am 8/30/12
	const int rows = 3;
	const int columns = 4;
	double** mat;

	int i, j;
	//allocate
	mat = new double*[rows];
	for (i = 0; i < rows; i++)
	{
		mat[i] = new double[columns];
	}

	//input
	int input = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			mat[i][j] = ++input;
		}
	}

	//construct
	LinSolver solver(mat, 3, 4);
	//use
	solver.output();
	solver.solve(true);

	//free
	for (i = 0; i < rows; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;

	return 0;
}

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "LinSolver.h"

using namespace std;

LinSolver::LinSolver(double** mat, int rows, int columns)
{
	m_mat = mat;
	m_rows = rows;
	m_columns = columns;
}


LinSolver::~LinSolver(void)
{
}

void LinSolver::solve(bool showWork)
{
	int i;

	for (i = 0; i < m_rows; i++)
	{
		reduceRow(i, showWork);
		eliminateColumn(i, showWork);
	}

	//shift all nonzero rows to the top
	//all nonzero vectors should already be in order relative to eachother
	//initialize isZeroVec array
	int j;
	bool* isZeroVec = new bool[m_rows];
	for (i = 0; i < m_rows; i++)
	{
		//see if this vector is zero or nonzero
		isZeroVec[i] = true;
		for (j = 0; j < m_columns; j++)
		{
			if (m_mat[i][j] != 0)
				isZeroVec[i] = false;
		}
	}

	//if zero from top, find and swap with next nonzero from bottom
	int fromTop = 0;
	int fromBot = m_rows - 1;
	while (fromTop < fromBot)
	{
		//find the first zeroVec from top
		while (!isZeroVec[fromTop] && fromTop < fromBot)
		{
			fromTop++;
		}

		//find the first nonzerovec from bottom
		while (isZeroVec[fromBot] && fromTop < fromBot)
		{
			fromBot--;
		}

		if (fromTop < fromBot)
		{
			swap<double*>(m_mat[fromTop], m_mat[fromBot]);
			swap<bool>(isZeroVec[fromTop], isZeroVec[fromBot]);
			if (showWork)
				output();
		}
	}

	delete[] isZeroVec;
}

void LinSolver::reduceRow(int row, bool showWork)
{
	int i;
	double divisor = m_mat[row][row];
	//guard clause
	//if div == 0 then ignore
	if (divisor == 0)
		return;

	for (i = row; i < m_columns; i++)
	{
		m_mat[row][i] /= divisor;
	}
	
	if (showWork)
		output();
}

void LinSolver::eliminateColumn(int column, bool showWork)
{
	int i, j;
	//guard for div by 0
	if (m_mat[column][column] == 0)
		return;

	//assume reduceRow has been called before, and the leading factor is a 1
	double cofactor;
	for (i = 0; i < m_rows; i++)
	{
		if (i == column)
			continue;
		
		//cofactor is whatever I need to multiply the current row by such that it 
		//adds to the target row and produces a zero in this column
		cofactor = -1 * m_mat[i][column] / m_mat[column][column];

		for (j = column; j < m_columns; j++)
		{
			//j = column because j = 0 would just be multiplying 0s if row is already
			//reduced
			m_mat[i][j] = m_mat[column][j] * cofactor + m_mat[i][j];
		}
	}
	
	if (showWork)
		output();
}

void LinSolver::output()
{
	int i, j;
	for (i = 0; i < m_rows; i++)
	{
		for (j = 0; j < m_columns; j++)
		{
			cout << setw(8) << m_mat[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

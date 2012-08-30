#pragma once

//computes a 2d matrix to reduced row echelon form
class LinSolver
{
public:
	//mat is in row major order
	LinSolver(double** mat, int rows, int columns);
	virtual ~LinSolver(void);
	void solve(bool showWork = false);
	void output();
protected:
	double** m_mat;
	int m_rows;
	int m_columns;
	void reduceRow(int row, bool showWork);
	void eliminateColumn(int column, bool showWork);
};

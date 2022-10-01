#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.h"

using std::string, std::vector, std::endl, std::cout, std::cin;

Matrix::Matrix()
{
	row = 100;
	col = 100;
	A = std::vector<std::vector<int> >(row, std::vector<int>(col, 0));
}

Matrix::Matrix(std::vector<std::vector<int> > mat)
{
	row = A.size();
	col = A[0].size();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			A[i][j] = mat[i][j];
	}
}

Matrix::Matrix(const Matrix &other)
{
	row = other.row;
	col = other.col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			A[i][j] = other.A[i][j];
	}
}

Matrix::~Matrix()
{
	A.clear();
}

Matrix &Matrix ::operator=(const Matrix &other)
{
	std::vector<std::vector<int> > B(other.row, std::vector<int>(other.col));
	for (int i = 0; i < other.row; i++)
	{
		for (int j = 0; j < other.col; j++)
			B[i][j] = other.A[i][j];
	}
	Matrix ans(B);
	return ans;
}

void Matrix::file_to_matrix(char *filename)
{
	std::ifstream f(filename);
	// this stores the first two lines into row and col
	f >> row >> col;

	A.resize(row, std::vector<int>(col));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			f >> A[i][j];
		}
	}
	f.close();
}

void Matrix::matrix_to_file(char *filename)
{
	std::ofstream f;
	f.open(filename);

	f << row << col;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 0)
			{
				f << A[i][j];
			}
			else
			{
				f << " " << A[i][j];
			}
		}
		f << std::endl;
	}
	f.close();
}

// Task 1
std::vector<int> Matrix::multiply_vector(std::vector<int> B)
{
	std::vector<int> C;
	for (int i = 0; i < col; i++)
	{
		int ans = 0;
		for (int j = 0; j < row; j++)
		{
			ans += (A[i][j] * B[j]);
		}
		C.push_back(ans);
	}
	return C;
}

int Matrix::count_mults(std::vector<int> B)
{
	int count = row * col;
	return count;
}

int Matrix::count_adds(std::vector<int> B)
{
	int count = row * (col - 1);
	return count;
}

// Task 2
Matrix Matrix::multiply(Matrix B)
{
	int R1 = row;
	int R2 = B.row;
	int C2 = B.col;

	std::vector<std::vector<int> > ans(R1, std::vector<int>(C2));
	for (int i = 0; i < R1; i++)
	{
		for (int j = 0; j < C2; j++)
		{
			ans[i][j] = 0;

			for (int k = 0; k < R2; k++)
			{
				ans[i][j] += (A[i][k] * B.A[k][j]);
			}
		}
	}
	Matrix C(ans);
	return C;
}

Matrix Matrix::transpose()
{
	std::vector<std::vector<int> > ans(row, std::vector<int>(col));
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
			ans[i][j] = A[j][i];
	Matrix T(ans);
	return T;
}

int Matrix::count_mults(Matrix B)
{
	int count = row * col * B.row;
	return count;
}

int Matrix::count_adds(Matrix B)
{
	int count = row * col * (B.row - 1);
	return count;
}

bool Matrix::is_multipliable(Matrix B)
{
	int row_of_B = B.row;
	if (col == row_of_B)
		return true;
	return false;
}

// Task 3
Matrix Matrix::kronecker(Matrix B)
{
	std::vector<std::vector<int> > ans(row * B.row, std::vector<int>(col * B.col));
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < B.row; k++)
		{
			for (int j = 0; j < col; j++)
			{
				for (int l = 0; l < B.col; l++)
				{
					ans[i + l + 1][j + k + 1] = A[i][j] * B.A[k][l];
				}
			}
		}
	}
	Matrix C(ans);
	return C;
}

int Matrix::count_mults_kron(Matrix B)
{
	int count = row * col * B.row * B.col;
	return count;
}
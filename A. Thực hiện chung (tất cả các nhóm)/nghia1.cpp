#include <iostream>
// #include <cstdio>
#include <omp.h>
#include <ctime>
// #include <cstdlib>
#include <omp.h>
#include <chrono>

using namespace std;

#define SIZE 10
// #define SIZE 100
// #define SIZE 300
// #define SIZE 500
// #define SIZE 700
// #define SIZE 900
// #define SIZE 1000
// #define SIZE 3000
// #define SIZE 5000
// #define SIZE 7000
// #define SIZE 9000
// #define SIZE 10000

double calculatorEfficiency(double time_tt, double time_ss, int thread);							   // Hàm tính hiệu suất
double generateRandomNumber();																		   // Hàm sinh giá trị ngẫu nhiên
double *createRandomMatrix(int row, int col);														   // Hàm tạo matrix ngẫu nhiên
double *createRandomVector(int size);																   // Hàm tạo vector ngẫu nhiên
void releaseMemory(double *matrix, double *vector, double *result);									   // Hàm giải phóng bộ nhớ
void displayMatrix(double *matrix, int row, int col);												   // Hàm hiển thị matrix
void displayVector(double *vector, int size);														   // Hàm hiển thị vector
void sequentialMultiplyMatrixVector(double *matrix, double *vector, double *result, int row, int col); // Hàm tính tuần tự
void parallelMultiplyMatrixVector(double *matrix, double *vector, double *result, int row, int col);   // Hàm tính song song

int main()
{
	int row = SIZE;
	int col = SIZE;
	int size = col;
	double *result = new double[row];
	double efficiency;
	cout << "The sizes: matrix = " << row << "x" << col << ", vector = " << size << "x1" << endl;

	// Tạo matrix và vector ngẫu nhiên
	double *matrix = createRandomMatrix(row, col);
	double *vector = createRandomVector(col);

	// Thực hiện tuần tự
	auto start_time_sequential = chrono::high_resolution_clock::now();
	sequentialMultiplyMatrixVector(matrix, vector, result, row, col);
	auto end_time_sequential = chrono::high_resolution_clock::now();
	auto duration_sequential = chrono::duration_cast<std::chrono::microseconds>(end_time_sequential - start_time_sequential);
	cout << "Sequential programming: " << endl;
	// displayVector(result, row);
	cout << "time = " << duration_sequential.count() << " microseconds" << endl;

	// Thực hiện song song
	int max_threads = omp_get_max_threads(); // Lấy số luồng tối đa theo từng máy
	for (int thread = 2; thread < max_threads; thread++)
	{
		omp_set_num_threads(thread); // Lặp theo số luồng để lấy thời gian
		auto start_time_parallel = chrono::high_resolution_clock::now();
		// result = parallelDotProduct(vectorA, vectorB, SIZE);
		parallelMultiplyMatrixVector(matrix, vector, result, row, col);
		auto end_time_parallel = chrono::high_resolution_clock::now();
		auto duration_parallel = chrono::duration_cast<std::chrono::microseconds>(end_time_parallel - start_time_parallel);
		efficiency = calculatorEfficiency(duration_sequential.count(), duration_parallel.count(), thread);
		cout << "Parallel: thread = " << thread << ", time = " << duration_parallel.count() << " microseconds"
			 << ", efficiency = " << efficiency << endl;
		// displayVector(result, row);
	}

	// Giải phóng bộ nhớ
	releaseMemory(matrix, vector, result);

	return 0;
}
double calculatorEfficiency(double time_tt, double time_ss, int thread)
{
	return (time_tt / time_ss) / thread;
}
double generateRandomNumber()
{
	static bool seedInitialized = false;

	// Kiểm tra khởi tạo seed
	if (!seedInitialized)
	{
		srand(time(NULL));
		seedInitialized = true;
	}

	return static_cast<double>(rand());
}
double *createRandomMatrix(int row, int col)
{
	double *matrix = new double[row * col];

	if (matrix == nullptr)
	{
		cerr << "Error: Failed to allocate memory." << endl;
		exit(1);
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i * col + j] = generateRandomNumber();
		}
	}

	return matrix;
}

double *createRandomVector(int size)
{
	double *vector = new double[size];

	if (vector == nullptr)
	{
		cerr << "Error: Failed to allocate memory." << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
	{
		vector[i] = generateRandomNumber();
	}

	return vector;
}
void releaseMemory(double *matrix, double *vector, double *result)
{
	delete[] matrix;
	delete[] vector;
	delete[] result;
}

void displayMatrix(double *matrix, int row, int col)
{
	cout << "Matrix: " << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i * col + j] << "\t";
		}
		cout << endl;
	}
}

void displayVector(double *vector, int size)
{
	cout << "Vector: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << vector[i] << "\t";
	}
	cout << endl;
}
void sequentialMultiplyMatrixVector(double *matrix, double *vector, double *result, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		result[i] = 0;
		for (int j = 0; j < col; j++)
		{
			result[i] += matrix[i * col + j] * vector[j];
		}
	}
}

void parallelMultiplyMatrixVector(double *matrix, double *vector, double *result, int row, int col)
{
	int i, j;
#pragma omp parallel for private(j)
	for (i = 0; i < row; i++)
	{
		result[i] = 0;
		for (j = 0; j < col; j++)
			result[i] += matrix[i * col + j] * vector[j];
	}
}

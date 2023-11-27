#include <iostream>

#include<iomanip>

#include <ctime>

#include <cstdlib>

// #include <chrono>

#include <omp.h>

// #define SIZE 10
// #define SIZE 100
// #define SIZE 1000
// #define SIZE 10000
// #define SIZE 100000
// #define SIZE 1000000
// #define SIZE 10000000
#define SIZE 100000000
// #define SIZE 1000000000

double generateRandomNumber();                                           // Hàm sinh giá trị ngẫu nhiên
double *createRandomVector(int size);                                    // Hàm tạo vector ngẫu nhiên
double sequentialDotProduct(double *vectorA, double *vectorB, int size); // Hàm tuần tự tính tích vô hướng của 2 vector
double parallelDotProduct(double *vectorA, double *vectorB, int size);   // Hàm song song tính tích vô hướng của 2 vector
double parallelDotProduct_v1(double *vectorA, double *vectorB, int size);

int main()
{
    std::cout << "The sizes of the 2 vectors are: " << SIZE << std::endl;

    double *vectorA = createRandomVector(SIZE);
    double *vectorB = createRandomVector(SIZE);

    // Thực hiện tuần tự
    double start_time_sequential =  omp_get_wtime();
    double result_sequential = sequentialDotProduct(vectorA, vectorB, SIZE);
    double end_time_sequential =  omp_get_wtime();
    double duration_sequential =  (end_time_sequential - start_time_sequential);
    std::cout << "Sequential programming" << std::endl;
    std::cout << "The dot product of two vectors is: " << result_sequential << std::endl;
    std::cout << "Program sequential execution time: " << duration_sequential << " seconds" << std::endl; // Tính thời gian thực thi

    // Thực hiện song song
    double start_time_parallel =  omp_get_wtime();
    long double result_parallel = parallelDotProduct(vectorA, vectorB, SIZE);
    double end_time_parallel   =  omp_get_wtime();
    double duration_parallel =  (end_time_parallel - start_time_parallel);
    std::cout << "Parallel programming" << std::endl;
    std::cout << "The dot product of two vectors is: " << result_parallel << std::endl;
    std::cout << "Program parallel execution time: " <<  std::setprecision(26) << duration_parallel << " seconds" << std::endl; // Tính thời gian thực thi

    
    // Thực hiện song song
    double start_time_parallel_v1 =  omp_get_wtime();
    long double result_parallel_v1 = parallelDotProduct_v1(vectorA, vectorB, SIZE);
    double end_time_parallel_v1   =  omp_get_wtime();
    double duration_parallel_v1 =  (end_time_parallel_v1 - start_time_parallel_v1);
    std::cout << "Parallel programming" << std::endl;
    std::cout << "The dot product of two vectors is: " << result_parallel_v1 << std::endl;
    std::cout << "Program parallel execution time: " << duration_parallel_v1   << " seconds" << std::endl; // Tính thời gian thực thi

    // Giải phóng bộ nhớ
    delete[] vectorA;
    delete[] vectorB;
    return 0;
}

double generateRandomNumber()
{
    static bool seedInitialized = false;

    // Nếu seed chưa được khởi tạo, hãy khởi tạo nó
    if (!seedInitialized)
    {
        srand(time(NULL));
        seedInitialized = true;
    }

    return static_cast<double>(rand());
}

double *createRandomVector(int size)
{
    double *vector = new double[size];

    if (vector == nullptr)
    {
        std::cerr << "Error: Failed to allocate memory." << std::endl;
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        vector[i] = generateRandomNumber();
    }

    return vector;
}

double sequentialDotProduct(double *vectorA, double *vectorB, int size)
{
    double result = 0.0;

    for (int i = 0; i < size; i++)
    {
        result += vectorA[i] * vectorB[i];
    }

    return result;
}

double parallelDotProduct(double *vectorA, double *vectorB, int size)
{

    long double result = 0.0;

#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < size; ++i)
    {
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        result += vectorA[i] * vectorB[i];
    }

    return result;
}

double parallelDotProduct_v1(double *vectorA, double *vectorB, int size)
{

    
    long double result = 0.0;

    #pragma omp parallel for reduction(+ : result), schedule(static)

    for (int i = 0; i < size; ++i)
    {
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        result += vectorA[i] * vectorB[i];
    }
    return result;
}
double parallelDotProduct_v2(double *vectorA, double *vectorB, int size)
{

    
    long double result = 0.0;

    #pragma omp parallel for reduction(+ : result), schedule(static)

    for (int i = 0; i < size; ++i)
    {
        result += vectorA[i] * vectorB[i];
    }
    return result;
}


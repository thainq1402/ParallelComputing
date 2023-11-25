#include <iostream>

#include <ctime>

#include <cstdlib>

#include <chrono>

#include <omp.h>

// #define SIZE 10
// #define SIZE 100
#define SIZE 1000
// #define SIZE 10000
// #define SIZE 100000
// #define SIZE 1000000
// #define SIZE 10000000
// #define SIZE 100000000
// #define SIZE 1000000000

double generateRandomNumber();                                           // Hàm sinh giá trị ngẫu nhiên
double *createRandomVector(int size);                                    // Hàm tạo vector ngẫu nhiên
double sequentialDotProduct(double *vectorA, double *vectorB, int size); // Hàm tuần tự tính tích vô hướng của 2 vector
double parallelDotProduct(double *vectorA, double *vectorB, int size);   // Hàm song song tính tích vô hướng của 2 vector

int main()
{
    std::cout << "The sizes of the 2 vectors are: " << SIZE << std::endl;

    double *vectorA = createRandomVector(SIZE);
    double *vectorB = createRandomVector(SIZE);

    // Thực hiện tuần tự
    auto start_time_sequential = std::chrono::high_resolution_clock::now(); // Lấy thời điểm bắt đầu
    double result_sequential = sequentialDotProduct(vectorA, vectorB, SIZE);
    auto end_time_sequential = std::chrono::high_resolution_clock::now(); // Lấy thời điểm kết thúc
    auto duration_sequential = std::chrono::duration_cast<std::chrono::microseconds>(end_time_sequential - start_time_sequential);
    std::cout << "Sequential programming" << std::endl;
    std::cout << "The dot product of two vectors is: " << result_sequential << std::endl;
    std::cout << "Program sequential execution time: " << duration_sequential.count() << " microseconds" << std::endl;      // Tính thời gian thực thi
    std::cout << "Program sequential execution time: " << duration_sequential.count() / 1000000 << " seconds" << std::endl; // Tính thời gian thực thi

    // Thực hiện song song
    auto start_time_parallel = std::chrono::high_resolution_clock::now(); // Lấy thời điểm bắt đầu
    double result_parallel = parallelDotProduct(vectorA, vectorB, SIZE);
    auto end_time_parallel = std::chrono::high_resolution_clock::now(); // Lấy thời điểm kết thúc
    auto duration_parallel = std::chrono::duration_cast<std::chrono::microseconds>(end_time_parallel - start_time_parallel);
    std::cout << "Parallel programming" << std::endl;
    std::cout << "The dot product of two vectors is: " << result_parallel << std::endl;
    std::cout << "Program parallel execution time: " << duration_parallel.count() << " microseconds" << std::endl;      // Tính thời gian thực thi
    std::cout << "Program parallel execution time: " << duration_parallel.count() / 1000000 << " seconds" << std::endl; // Tính thời gian thực thi

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

    double result = 0.0;

#pragma fomp parallel for reduction(+ : result)
    for (int i = 0; i < size; ++i)
    {
        // int threadNum = omp_get_thread_num();
        // std::cout << "Thread " << threadNum << " is processing element " << i << std::endl;
        result += vectorA[i] * vectorB[i];
    }

    return result;
}

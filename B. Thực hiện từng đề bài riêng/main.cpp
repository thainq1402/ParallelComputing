#include <iostream>
#include <ctime>
#include <cstdlib>
// #include<iomanip>
#include <omp.h>
#include <chrono>
#include<random>

using namespace std;

// #define SIZE 10
// #define SIZE 100
// #define SIZE 1000
// #define SIZE 10000
// #define SIZE 100000
#define SIZE 1000000
// #define SIZE 10000000
// #define SIZE 100000000
// #define SIZE 1000000000
double calculatorEfficiency(double time_tt, double time_ss, int thread); // Hàm tính hiệu suất
double generateRandomNumber();                                           // Hàm sinh giá trị ngẫu nhiên
double *createRandomVector(int size);                                    // Hàm tạo vector ngẫu nhiên
void releaseMemory(double *vectorA, double *vectorB);                    // Hàm giải phóng bộ nhớ
double sequentialDotProduct(double *vectorA, double *vectorB, int size); // Hàm tính tuần tự
double parallelDotProduct(double *vectorA, double *vectorB, int size);   // Hàm tính song song
int main()
{
    double result, efficiency;
    cout << "The sizes of the 2 vectors are: " << SIZE << endl;

    // Tạo 2 vector ngẫu nhiên
    double *vectorA = createRandomVector(SIZE);
    double *vectorB = createRandomVector(SIZE);

    // Thực hiện tuần tự
    auto start_time_sequential = chrono::high_resolution_clock::now();
    result = sequentialDotProduct(vectorA, vectorB, SIZE);
    auto end_time_sequential = chrono::high_resolution_clock::now();
    auto duration_sequential = chrono::duration_cast<std::chrono::microseconds>(end_time_sequential - start_time_sequential);
    cout << "Sequential programming: result = " << result << ", time = " << duration_sequential.count() << " microseconds" << endl;

    // Thực hiện song song
    int max_threads = omp_get_max_threads(); // Lấy số luồng tối đa theo từng máy
    for (int thread = 2; thread < max_threads; thread++)
    {
        omp_set_num_threads(thread); // Lặp theo số luồng để lấy thời gian
        auto start_time_parallel = chrono::high_resolution_clock::now();
        result = parallelDotProduct(vectorA, vectorB, SIZE);
        auto end_time_parallel = chrono::high_resolution_clock::now();
        auto duration_parallel = chrono::duration_cast<std::chrono::microseconds>(end_time_parallel - start_time_parallel);
        efficiency = calculatorEfficiency(duration_sequential.count(), duration_parallel.count(), thread);
        cout << "Parallel: thread = " << thread << ", result = " << result << ", time = " << duration_parallel.count() << " microseconds"
             << ", efficiency = " << efficiency << endl;
    }

    // Giải phóng bộ nhớ
    releaseMemory(vectorA, vectorB);

    return 0;
}
double calculatorEfficiency(double time_tt, double time_ss, int thread)
{
    return (time_tt / time_ss) / thread;
}
double generateRandomNumber()
{
    // static bool seedInitialized = false;

    // // Kiểm tra khởi tạo seed
    // if (!seedInitialized)
    // {
    //     srand(time(NULL));
    //     seedInitialized = true;
    // }

    // return static_cast<double>(rand());
    std::random_device rd;  // Thiết bị ngẫu nhiên
    std::mt19937 gen(rd()); // Máy phát sinh số ngẫu nhiên

    // Phân phối ngẫu nhiên hữu tỉ trong khoảng từ 0 đến 1
    std::uniform_real_distribution<double> dis(0.0, 100.0);

    // Sinh số hữu tỉ ngẫu nhiên
    double randomValue = dis(gen);
    return randomValue;

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
void releaseMemory(double *vectorA, double *vectorB)
{
    delete[] vectorA;
    delete[] vectorB;
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

#pragma omp parallel for reduction(+ : result), schedule(static)
    for (int i = 0; i < size; ++i)
    {
        result += vectorA[i] * vectorB[i];
    }

    return result;
}

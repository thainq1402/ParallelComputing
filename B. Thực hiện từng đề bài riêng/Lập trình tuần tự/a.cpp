#include <stdio.h>

#include <time.h>

#include <stdlib.h>
#include <stdbool.h>

#include <omp.h>

#define SIZE 1000000000
// #define SIZE 1000000
// #define SIZE 10000
// #define SIZE 10

double generateRandomNumber();                                           // Hàm sinh giá trị ngẫu nhiên
double *createRandomVector(int size);                                    // Hàm tạo vector ngẫu nhiên
double sequentialDotProduct(double *vectorA, double *vectorB, int size); // Hàm tuần tự tính tích vô hướng của 2 vector

int main()
{
    printf("The sizes of the 2 vectors are: %d\n", SIZE);

    double *vectorA = createRandomVector(SIZE);
    double *vectorB = createRandomVector(SIZE);

    clock_t start_time = clock(); // Lấy thời điểm bắt đầu

    // Thực hiện tuần tự tính tích vô hướng của 2 vector
    double result = sequentialDotProduct(vectorA, vectorB, SIZE);

    clock_t end_time = clock(); // Lấy thời điểm kết thúc

    printf("Sequential programming\n");

    printf("The dot product of two vectors is: %f\n", result);

    printf("Program execution time: %lf microseconds\n", ((double)(end_time - start_time))); // Tính thời gian thực thi

    // Giải phóng bộ nhớ
    free(vectorA);
    free(vectorB);
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

    return (double)rand();
}
double *createRandomVector(int size)
{
    double *vector = (double *)malloc(size * sizeof(double));

    if (vector == NULL)
    {
        printf("Error: Failed to allocate memory.");
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

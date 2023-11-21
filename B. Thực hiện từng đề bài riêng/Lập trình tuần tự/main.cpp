#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <random>
#include <omp.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

// Config
const string INPUT_FOLDER = "data/10"; // Thư mục input chứa file dữ liệu vector_a.txt và vector_b.txt

// Hàm đọc vector từ file
vector<double> readVectorFromFile(const fs::path &inputFile)
{
    ifstream file(inputFile);

    // Kiểm tra xem file có mở thành công hay không?
    if (!file.is_open())
    {
        cerr << "Cannot open file: " << inputFile << endl;
        return vector<double>();
    }

    vector<double> resultVector;
    double value;

    // Đọc từng giá trị từ file và thêm vào vector
    while (file >> value)
    {
        resultVector.push_back(value);
    }

    // Đóng file sau khi đọc xong
    file.close();

    return resultVector;
}

// Hàm tuần tự tính tích vô hướng của hai vector
double dotProduct(const vector<double> &a, const vector<double> &b)
{
    double result = 0.0;

    for (size_t i = 0; i < a.size(); i++)
    {
        result += a[i] * b[i];
    }

    return result;
}
int main()
{
    auto start = chrono::high_resolution_clock::now();
    //@ ===================================
    // Đọc hai vector từ các tệp
    vector<double> vectorA = readVectorFromFile(fs::path(INPUT_FOLDER) / "vector_a.txt");
    vector<double> vectorB = readVectorFromFile(fs::path(INPUT_FOLDER) / "vector_b.txt");

    // Kiểm tra kích thước
    if (vectorA.size() == 0)
    {
        cout << "Vector A is empty." << endl;
        return 1;
    }

    if (vectorB.size() == 0)
    {
        cout << "Vector B is empty." << endl;
        return 1;
    }

    // vectorA.push_back(123456789);
    if (vectorA.size() != vectorB.size())
    {
        cout << "The sizes of the two vectors are not equal." << endl;
        return 1;
    }

    // Tính tích vô hướng và in kết quả
    double result = dotProduct(vectorA, vectorB);
    cout << "Sequential programming" << endl;
    cout << "Input directory: \'" << INPUT_FOLDER << "\'" << endl;
    cout << "The dot product of two vectors is: " << result << endl;
    //@ ===================================
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Program execution time: " << duration.count() << " microseconds" << endl;
    return 0;
}

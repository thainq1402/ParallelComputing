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
const int BATCH_SIZE = 1000;         // Số lượng xử lý ghi phần tử vector
const double MIN_VALUE = 1.0;        // Giá trị lớn nhất trong vector ngẫu nhiên
const double MAX_VALUE = 100.0;      // Giá trị nhỏ nhất trong vector ngẫu nhiên
const string OUTPUT_FOLDER = "data"; // Thư mục output chứa file dữ liệu

// Hàm ghi 1 vector vào tệp
void writeVectorToFile(const vector<double> &inputVector, const fs::path &outputFile)
{
    ofstream file(outputFile);

    // Kiểm tra xem file có mở thành công hay không?
    if (!file.is_open())
    {
        cerr << "Cannot open file: " << outputFile << endl;
        return;
    }

    // Ghi dữ liệu từ vector vào file theo từng BATCH_SIZE
    for (size_t i = 0; i < inputVector.size(); i += BATCH_SIZE)
    {
        for (size_t j = i; j < min(i + BATCH_SIZE, inputVector.size()); ++j)
        {
            file << inputVector[j] << " ";
        }
        file << "\n";
    }

    // Đóng file sau khi thực hiện xong
    file.close();
}

void generateRandomVector(const int length)
{
    // Khởi tạo generator ngẫu nhiên
    default_random_engine generator;
    uniform_real_distribution<double> distribution(MIN_VALUE, MAX_VALUE);

    // Tạo vector ngẫu nhiên
    vector<double> vector_a;
    vector<double> vector_b;

    for (int i = 0; i < length; i++)
    {
        double random_value = distribution(generator);
        vector_a.push_back(random_value);

        random_value = distribution(generator);
        vector_b.push_back(random_value);
    }

    // Ghi kết quả vector vào tệp
    if (!fs::exists(fs::path(OUTPUT_FOLDER) / to_string(length)))
    {
        fs::create_directory(fs::path(OUTPUT_FOLDER) / to_string(length));
    }

    writeVectorToFile(vector_a, fs::path(OUTPUT_FOLDER) / to_string(length) / "vector_a.txt");
    writeVectorToFile(vector_b, fs::path(OUTPUT_FOLDER) / to_string(length) / "vector_b.txt");

    cout << "Successfully generated 2 random vectors of length: " << length << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    //@ ===================================

    // Kiểm tra thư mục output có tồn tại, nếu không thì tạo thư mục output
    if (!fs::exists(OUTPUT_FOLDER))
    {
        fs::create_directory(OUTPUT_FOLDER);
    }

    // Độ dài của vector
    // int array_of_vector_lengths[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    int array_of_vector_lengths[] = {10, 100, 1000};

    // #pragma omp parallel for
    for (int i = 0; i < sizeof(array_of_vector_lengths) / sizeof(array_of_vector_lengths[0]); ++i)
    {

        generateRandomVector(array_of_vector_lengths[i]);
    }
    //@ ===================================
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Program execution time: " << duration.count() << " microseconds" << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;


// Hàm ghi một vector vào tệp
void writeVectorToFile(const string &filename, const vector<double> &data_vector)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < data_vector.size(); i++)
        {
            file << fixed << setprecision(2) << data_vector[i] << "\n"; // Định dạng số thập phân với 2 chữ số sau dấu phẩy
        }
        file.close();
    }
    else
    {
        cerr << "Cannot open file: " << filename << endl;
    }
}

int main()
{
    // Độ dài của vector
    long long int length = 100000000;
    // long long int length = 10;
    // long long int length = 100;
    // long long int length = 1000;
    // long long int length = 10000;
    // long long int length = 100000;
    // long long int length = 1000000;
    // long long int length = 10000000;

    // Khởi tạo generator ngẫu nhiên
    default_random_engine generator;
    // Tạo số ngẫu nhiên từ 1 đến 100
    uniform_real_distribution<double> distribution(1.0, 100.0);

    // Tạo vector ngẫu nhiên
    vector<double> vectorA;
    vector<double> vectorB;

    for (int i = 0; i < length; i++)
    {
        double random_value = distribution(generator);
        vectorA.push_back(random_value);

        random_value = distribution(generator);
        vectorB.push_back(random_value);
    }

    // Ghi kết quả vào tệp vector_a.txt
    writeVectorToFile("vector_a.txt", vectorA);

    // Ghi kết quả vào tệp vector_b.txt
    writeVectorToFile("vector_b.txt", vectorB);

    cout << "Generated 2 random vectors." << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

// Hàm ghi một vector vào tệp
void writeVectorToFile(const std::string &filename, const std::vector<double> &data)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < data.size(); i++)
        {
            file << std::fixed << std::setprecision(2) << data[i] << "\n"; // Định dạng số thập phân với 2 chữ số sau dấu phẩy
        }
        file.close();
    }
    else
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
    }
}

int main()
{
    // Độ dài của vector
    long long int length = 1000000000000;

    // Khởi tạo generator ngẫu nhiên
    std::default_random_engine generator;
    // Tạo số ngẫu nhiên từ 1 đến 100
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // Tạo vector ngẫu nhiên
    std::vector<double> vectorA;
    std::vector<double> vectorB;

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

    std::cout << "Generated 2 random vectors." << std::endl;

    return 0;
}

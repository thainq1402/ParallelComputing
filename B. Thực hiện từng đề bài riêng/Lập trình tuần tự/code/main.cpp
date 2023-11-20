#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>

// Hàm đọc một vector từ tệp
std::vector<double> readVectorFromFile(const std::string &filename)
{
    std::vector<double> result;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        double value;
        while (ss >> value)
        {
            result.push_back(value);
        }
    }

    file.close();
    return result;
}

// Hàm tính tích vô hướng của hai vector
double dotProduct(const std::vector<double> &a, const std::vector<double> &b)
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
    try
    {
        // Đọc hai vector từ các tệp
        std::vector<double> vectorA = readVectorFromFile("vector_a.txt");
        std::vector<double> vectorB = readVectorFromFile("vector_b.txt");

        // In hai vector
        std::cout << "Vector A: ";
        for (const double &value : vectorA)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        std::cout << "Vector B: ";
        for (const double &value : vectorB)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        // Kiểm tra kích thước
        if (vectorA.size() != vectorB.size())
        {
            std::cout << "The sizes of the two vectors are not equal." << std::endl;
            return 1;
        }

        // Tính tích vô hướng và in kết quả
        double result = dotProduct(vectorA, vectorB);
        std::cout << "The dot product of two vectors is: " << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#include <iostream>
#include <random>

int main() {
    std::random_device rd;  // Thiết bị ngẫu nhiên
    std::mt19937 gen(rd()); // Máy phát sinh số ngẫu nhiên

    // Phân phối ngẫu nhiên hữu tỉ trong khoảng từ 0 đến 1
    std::uniform_real_distribution<double> dis(0.0, 100.0);

    // Sinh số hữu tỉ ngẫu nhiên
    double randomValue = dis(gen);

    // In số hữu tỉ ngẫu nhiên
    std::cout << "Số hữu tỉ ngẫu nhiên: " << randomValue << std::endl;

    return 0;
}
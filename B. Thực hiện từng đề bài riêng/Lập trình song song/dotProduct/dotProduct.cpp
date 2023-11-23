#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;


vector<double> readVectorFromFile(const string& filename); // Hàm đọc vector từ file txt
double dotProductOPM(vector<double> vectorA, vector<double> vectorB); // Nhân vô hướng 2 vecto 




int main() {
    // Tạo hai biến để lưu hai vector từ hai tệp khác nhau
    vector<double> vectorA, vectorB;

    // Lưu vector từ tệp "file1.txt" vào biến vectorA
    vectorA = readVectorFromFile("vectorA.txt");

    // Lưu vector từ tệp "file2.txt" vào biến vectorB
    vectorB = readVectorFromFile("vectorB.txt");

    double dotPro = dotProductOPM(vectorA,vectorB);
    cout << "Dot product: " << dotPro << endl;

    cout << endl;

    return 0;
}
// Hàm để đọc vector từ một tệp và trả về vector
vector<double> readVectorFromFile(const string& filename) {
    // Mở tệp văn bản để đọc
    ifstream file(filename);

    // Kiểm tra xem tệp có mở thành công không
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        // Trả về vector rỗng nếu có lỗi
        return vector<double>();
    }

    // Đọc dữ liệu từ tệp vào một vector
    vector<double> vector;
    double value;

    while (file >> value) {
        vector.push_back(value);
    }

    // Đóng tệp sau khi đọc xong
    file.close();

    // Trả về vector đã đọc từ tệp
    return vector;
}

double dotProductOPM(const vector<double> vectorA, const vector<double> vectorB) {
    if (vectorA.size() != vectorB.size()) {
        cerr << "Error: Vectors must have the same size." << endl;
        return 0.0;
    }

    double result = 0.0;
    int leng = vectorA.size();

    #pragma fomp parallel for reduction(+:result)
    for (size_t i = 0; i < vectorA.size(); ++i) {
        int threadNum = omp_get_thread_num();
        cout << "Thread " << threadNum << " is processing element " << i << endl;
        result += vectorA[i] * vectorB[i];
    }

    return result;
}

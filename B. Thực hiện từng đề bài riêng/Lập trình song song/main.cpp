#include <stdio.h>
#include<string.h>
#include <vector>
#include <iostream>

using namespace std;
int main() {
    vector<double> vectorA;
    vector<double> vectorB;
    vectorA.push_back(1.2);
    vectorA.push_back(2.3);
    
    #pragma omp  parallel
    for (int i=0; i<100; i++)
    {
        vectorA.push_back(i);
    }
    
    
    for (const double &value : vectorA)
    {
        cout << value << "\t";
    }
}
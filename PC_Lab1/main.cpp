#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <thread>

void printSystemInfo() {
    unsigned int logicalCores = std::thread::hardware_concurrency();
    std::cout << "Logical cores: " << logicalCores << "\n";
    
    int mib[2], physicalCores = 0;
        size_t len = sizeof(physicalCores);
        mib[0] = CTL_HW;
        mib[1] = HW_AVAILCPU;
        sysctl(mib, 2, &physicalCores, &len, nullptr, 0);
        std::cout << "Physical cores: " << physicalCores << "\n";

        int64_t memSize = 0;
        size_t sizeLen = sizeof(memSize);
        int mibMem[2] = {CTL_HW, HW_MEMSIZE};
        sysctl(mibMem, 2, &memSize, &sizeLen, nullptr, 0);
        std::cout << "RAM approx: " << (memSize >> 20) << " MB\n";
}


int main() {
    
    printSystemInfo();
    
    int N = 10;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    
    std::vector<std::vector<long long>> matrix(N, std::vector<long long>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = std::rand() % 100;
            }
        }
    
    /*std::cout << "Початкова матриця:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";*/
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int col = 0; col < N; col++) {
            long long columnSum = 0;
            for (int row = 0; row < N; row++) {
                columnSum += matrix[row][col];
            }
          
            matrix[col][col] = columnSum;
        }
    auto end = std::chrono::high_resolution_clock::now();

        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    /*std::cout << "Результуюча матриця:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }*/

        std::cout << "Час виконання (мілісекунди): " << durationMs << " ms\n";
    return 0;
}

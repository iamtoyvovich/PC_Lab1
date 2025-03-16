#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>


int main() {
    int N = 1000;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    
    std::vector<std::vector<long long>> matrix(N, std::vector<long long>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = std::rand() % 100;
            }
        }
    
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

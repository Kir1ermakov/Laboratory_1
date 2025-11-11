#include <iostream>
#include "header.h"

int main() {
    const std::string filename = "matrix.bin";
    
    std::vector<std::vector<char>> matrix = {
        {10, 20, 30, 50},
        {40, 70, 48, 37},
        {52, 62, 62, 64}
    };

    if (writeMatrixToBinaryFile(filename, matrix)) {
        std::cout << "Файл записан. Размер: " 
                  << (matrix.size() * matrix[0].size()) << " байт\n";
    } else {
        return 1;
    }

    std::vector<std::vector<char>> loaded_matrix;
    if (readMatrixFromBinaryFile(filename, loaded_matrix, 3, 4)) {
        std::cout << "Прочитанная матрица:\n";
        for (const auto& row : loaded_matrix) {
            for (char num : row) {
                std::cout << static_cast<int>(num) << " "; 
            }
            std::cout << "\n";
        }
    }

    return 0;
}
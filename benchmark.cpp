// Простой бенчмарк для измерения времени выполнения
#include <iostream>
#include <chrono>
#include "src/imageB.h"

int main() {
    const int WIDTH = 1000;
    const int HEIGHT = 1000;

    Image img;
    img.width = WIDTH;
    img.height = HEIGHT;
    img.pixels.resize(HEIGHT, std::vector<int>(WIDTH));
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            img.pixels[y][x] = (x + y) % 256;
        }
    }
    
    #ifdef USE_OPENMP
    std::cout << "ПАРАЛЛЕЛЬНАЯ версия\n";
    #else
    std::cout << "ПОСЛЕДОВАТЕЛЬНАЯ версия\n";
    #endif
    
    auto start = std::chrono::high_resolution_clock::now();
    
    rotateClockwise(img);
    rotateCounterClockwise(img);
    applyGaussianFilter(img);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Время выполнения: " << duration.count() << " мс\n";
    
    return 0;
}


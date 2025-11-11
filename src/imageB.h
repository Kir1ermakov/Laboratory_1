// Кирилл Ермаков
// Б82
// st130061@student.spbu.ru
// Laboratory1

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

struct Image {
    int width, height;  
    std::vector<std::vector<int>> pixels;
};

Image loadBinGrayImage(const std::string& filename, int width, int height);
void rotateClockwise(Image& img);
void rotateCounterClockwise(Image& img);
void applyGaussianFilter(Image& img);
void saveBinImage(const std::string& filename, const Image& img);
void printBinImage(Image& img);

#endif // IMAGE_H

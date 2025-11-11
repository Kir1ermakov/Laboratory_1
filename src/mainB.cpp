// Кирилл Ермаков
// Б82
// st130061@student.spbu.ru
// Laboratory1

#include <iostream>
#include "imageB.h"

int main()
{
    std::string inputFilename = "matrix.bin"; // имя файла с сырыми данными

    int width, height;
    std::cout << "Введите высоту изображения: ";
    std::cin >> height;
    std::cout << "Введите ширину изображения: ";
    std::cin >> width;

    Image img = loadBinGrayImage(inputFilename, width, height);

    printBinImage(img); //реализовано в ImageB.cpp. //Позволяет вывести небольшие bin файлы в конcоль.

    rotateClockwise(img);

    printBinImage(img);

    saveBinImage("images/rotateClockwise.bin", img);

    rotateCounterClockwise(img);

    printBinImage(img);

    saveBinImage("images/rotateCounterClockwise.bin", img);

    applyGaussianFilter(img);

    printBinImage(img);

    saveBinImage("images/filtered.bin", img);


    std::cout << "Обработка завершена!" << std::endl;
    return 0;
}
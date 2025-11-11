// Кирилл Ермаков
// Б82
// st130061@student.spbu.ru
// Laboratory1
/**
 * @file imageB.h
 * @brief Интерфейсы обработки изображений (градации серого).
 * @defgroup image_processing Обработка изображений
 * Набор функций для загрузки, поворота, фильтрации и сохранения
 * изображений в градациях серого.
 * @{ 
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

/**
 * @brief Простая структура градаций серого.
 */
struct Image {
    int width, height;  ///< Размеры изображения.
    std::vector<std::vector<int>> pixels; ///< Матрица пикселей в диапазоне 0-255.
};

/**
 * @brief Загружает бинарное изображение в градациях серого фиксированного размера.
 * @param filename Имя файла.
 * @param width Ширина изображения.
 * @param height Высота изображения.
 * @return Загруженное изображение.
 */
Image loadBinGrayImage(const std::string& filename, int width, int height);

/**
 * @brief Поворачивает изображение по часовой стрелке.
 * @param img Изображение для модификации.
 */
void rotateClockwise(Image& img);

/**
 * @brief Поворачивает изображение против часовой стрелки.
 * @param img Изображение для модификации.
 */
void rotateCounterClockwise(Image& img);

/**
 * @brief Применяет 3x3 гауссов фильтр к изображению.
 * @param img Изображение для модификации.
 */
void applyGaussianFilter(Image& img);

/**
 * @brief Сохраняет изображение в бинарный файл.
 * @param filename Имя файла.
 * @param img Исходное изображение.
 */
void saveBinImage(const std::string& filename, const Image& img);

/**
 * @brief Выводит содержимое изображения в стандартный поток.
 * @param img Изображение для вывода.
 */
void printBinImage(Image& img);

#endif // IMAGE_H

/** @} */

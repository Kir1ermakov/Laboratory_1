#ifndef BIN_FILE_WRITER_H
#define BIN_FILE_WRITER_H

#include <iostream>
#include <fstream>
#include <vector>

/**
 * @file header.h
 * @brief Интерфейс для записи/чтения матрицы байтов в бинарный файл.
 */

/**
 * @brief Записывает матрицу чисел (char) в бинарный файл. Каждое число — 1 байт.
 * @param filename Имя файла (например, "matrix.bin").
 * @param data Матрица данных (диапазон значений -128..127).
 * @return true, если запись прошла успешно.
 */
bool writeMatrixToBinaryFile(const std::string& filename, const std::vector<std::vector<char>>& data);

/**
 * @brief Читает матрицу чисел (char) из бинарного файла указанного размера.
 * @param filename Имя файла.
 * @param data Выходная матрица.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return true, если чтение прошло успешно.
 */
bool readMatrixFromBinaryFile(const std::string& filename, std::vector<std::vector<char>>& data, size_t rows, size_t cols);

#endif // BIN_FILE_WRITER_H
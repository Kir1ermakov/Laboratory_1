#ifndef BIN_FILE_WRITER_H
#define BIN_FILE_WRITER_H

#include <iostream>
#include <fstream>
#include <vector>

bool writeMatrixToBinaryFile(const std::string& filename, const std::vector<std::vector<char>>& data);

bool readMatrixFromBinaryFile(const std::string& filename, std::vector<std::vector<char>>& data, size_t rows, size_t cols);

#endif // BIN_FILE_WRITER_H
#include "header.h"

bool writeMatrixToBinaryFile(const std::string& filename, const std::vector<std::vector<char>>& data) {
    std::ofstream out_file(filename, std::ios::binary);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return false;
    }

    for (const auto& row : data) {
        out_file.write(row.data(), row.size());
    }

    out_file.close();
    return true;
}

bool readMatrixFromBinaryFile(const std::string& filename, std::vector<std::vector<char>>& data, size_t rows, size_t cols) {
    std::ifstream in_file(filename, std::ios::binary);
    if (!in_file) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return false;
    }

    // Проверка размера файла
    in_file.seekg(0, std::ios::end);
    size_t file_size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);

    if (file_size != rows * cols) {
        std::cerr << "Ошибка: размер файла не соответствует ожидаемому!" << std::endl;
        return false;
    }

    data.resize(rows);
    for (size_t i = 0; i < rows; ++i) {
        data[i].resize(cols);
        in_file.read(data[i].data(), cols);
    }

    in_file.close();
    return true;
}
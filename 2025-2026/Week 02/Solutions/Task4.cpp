#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

namespace MatrixConstants {
    const int MAX_SIZE = 100;
    const int MAX_INT_LEN = 20;
}

namespace MatrixUtils {
    unsigned charToDigit(char ch) {
        return ch - '0';
    }

    unsigned convertStrToUnsigned(const char* str) {
        unsigned res = 0;
        while (*str) {
            res = ((res * 10) + charToDigit(*str));
            str++;
        }
        return res;
    }

    size_t getFileLength(std::ifstream& ifs) {
        size_t currPos = ifs.tellg(), res = 0;
        ifs.seekg(0, std::ios::end);
        res = ifs.tellg();
        ifs.seekg(currPos, std::ios::beg);
        return res;
    }

    unsigned getCharCountFromFile(std::ifstream& ifs, char ch) {
        size_t currentPosition = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        if (!ifs.is_open())
            return 0;

        unsigned int count = 0;

        while (true) {
            char current = ifs.get();
            if (ifs.eof()) {
                break;
            }
            if (current == ch) {
                count++;
            }
        }

        ifs.clear();
        ifs.seekg(currentPosition);
        return count;
    }
}

struct Matrix {
    unsigned matrix[MatrixConstants::MAX_SIZE][MatrixConstants::MAX_SIZE];
    unsigned rows;
    unsigned colls;
};


void loadMatrix(Matrix& matrix, const char* fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return;
    }

    matrix.rows = MatrixUtils::getCharCountFromFile(file, '|') + 1;
    matrix.colls = MatrixUtils::getCharCountFromFile(file, ',') / matrix.rows + 1;

    file.seekg(0, std::ios::beg);
    char buff[MatrixConstants::MAX_INT_LEN];

    for (int i = 0; i < matrix.rows - 1; i++) {
        for (int j = 0; j < matrix.colls - 1; j++) {
            file.getline(buff, MatrixConstants::MAX_INT_LEN, ',');
            matrix.matrix[i][j] = MatrixUtils::convertStrToUnsigned(buff);
        }
        file.getline(buff, MatrixConstants::MAX_INT_LEN, '|');
        matrix.matrix[i][matrix.colls - 1] = MatrixUtils::convertStrToUnsigned(buff);
    }

    for (int j = 0; j < matrix.colls - 1; j++) {
        file.getline(buff, MatrixConstants::MAX_INT_LEN, ',');
        matrix.matrix[matrix.rows - 1][j] = MatrixUtils::convertStrToUnsigned(buff);
    }
    file.getline(buff, MatrixConstants::MAX_INT_LEN);
    matrix.matrix[matrix.rows - 1][matrix.colls - 1] = MatrixUtils::convertStrToUnsigned(buff);

    file.close();
}

Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2) {
    Matrix result;
    result.rows = matrix1.rows;
    result.colls = matrix2.colls;

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.colls; j++) {
            result.matrix[i][j] = 0;

            for (int k = 0; k < matrix2.rows; k++) {
                result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }

    return result;
}

Matrix matrixMultiplicationFromFile(const char* file1, const char* file2) {
    Matrix matrix1;
    Matrix matrix2;

    loadMatrix(matrix1, file1);
    loadMatrix(matrix2, file2);

    Matrix result = matrixMultiplication(matrix1, matrix2);
    return result;
}

Matrix matrixMultiplicationFromFile(const char* file1, const char* file2, const char* fileToSave) {
    Matrix res = matrixMultiplicationFromFile(file1, file2);

    std::ofstream saveFile(fileToSave, std::ios::trunc);
    if (!saveFile.is_open()) 
        return res;
  
    for (int i = 0; i < res.rows - 1; i++) {
        for (int j = 0; j < res.colls - 1; j++) {

            saveFile << std::to_string(res.matrix[i][j]) << ',';
        }
        saveFile << std::to_string(res.matrix[i][res.colls - 1]) << '|';
    }
    for (int j = 0; j < res.colls - 1; j++) {
        saveFile << std::to_string(res.matrix[res.rows - 1][j]) << ',';
    }

    saveFile << std::to_string(res.matrix[res.rows - 1][res.colls - 1]) << std::endl;

    saveFile.close();
    return res;
}


Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2) {
    Matrix result;
    result.rows = matrix1.rows;
    result.colls = matrix2.colls;

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.colls; j++) {
            result.matrix[i][j] = 0;

            for (int k = 0; k < matrix2.rows; k++) {
                result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }

    return result;
}

Matrix matrixMultiplicationFromFile(const char* file1, const char* file2)  {
    Matrix matrix1;
    Matrix matrix2;

    loadMatrix(matrix1, file1);
    loadMatrix(matrix2, file2);

    Matrix result = matrixMultiplication(matrix1, matrix2);
    return result;
}
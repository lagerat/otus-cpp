#include <iostream>
#include "matrix.h"

int main(int, char**) {
    Matrix<int, -1> matrixFirst;

    auto a = matrixFirst[0][0];
    assert(a == -1);
    assert(matrixFirst.size() == 0);

    matrixFirst[100][100] = 314;
    assert(matrixFirst[100][100] == 314);
    assert(matrixFirst.size() == 1);

    matrixFirst.clear();

    Matrix<int, 0> matrix;
    const int size = 10;
    for (auto i = 0; i < size; i++) {
        matrix[i][i] = i;
        matrix[i][size - i - 1] = size - i - 1;
    }

    const auto l = 1;
    const auto r = 9;
    for (auto i = l; i < r; i++) {
        for (auto j = l; j < r; j++) {
            std::cout << matrix[i][j].get() << ' ';
        }
        std::cout << '\n';
    }

    std::cout << matrix.size() << '\n';
    for (auto [cell_idx, cell_value] : matrix) {
        const auto [x, y] = cell_idx;
        std::cout << x << ' ' << y << ' ' << cell_value << '\n';
    }
    return 0;
}

#include "matrix.h"

#include <iostream>
#include <cassert>
#include <sstream>

int main()
{
    {
        Matrix<int, -1> matrix;
        assert(matrix.size() == 0);

        auto a = matrix[0][0];
        assert(a == -1);
        assert(matrix.size() == 0);

        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);
    }

    Matrix<int, 0> matrix;

    size_t size = 10;
    size_t c0 = 0;
    size_t c1 = 9;

    std::stringstream out;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (i == j) {
                matrix[i][j] = c0++;

                if (matrix[i][j] != 0)
                    out << "[" << i << "][" << j << "] = " << matrix[i][j] << std::endl;
            }

            if (i + j == size - 1) {
                matrix[i][j] = c1--;

                if (matrix[i][j] != 0)
                    out << "[" << i << "][" << j << "] = " << matrix[i][j] << std::endl;
            }
        }
    }

    for (size_t i = 1; i < 9; ++i) {
        for (size_t j = 1; j < 9; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "matrix size = " << matrix.size() << std::endl;
    std::cout << out.str();

    return 0;
}

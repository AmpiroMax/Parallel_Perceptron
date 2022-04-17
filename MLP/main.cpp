#include <iostream>
#include <vector>

#include "matrix/Matrix.h"

using std::size_t;

int main()
{
    std::vector<std::vector<double>> table(3, std::vector<double>(4));

    double counter = 0;

    for (size_t i = 0; i < table.size(); ++i)
        for (size_t j = 0; j < table[0].size(); ++j)
            table[i][j] = ++counter;

    Matrix matrix(table, 1, AlgorithmType::Slow);

    std::cout << matrix << "\n";
    std::cout << matrix * 5 << "\n";
    std::cout << matrix.T() << "\n";
    std::cout << 10 + matrix << "\n";
    std::cout << matrix - 7 << "\n";
    std::cout << 7 - matrix << "\n";
}

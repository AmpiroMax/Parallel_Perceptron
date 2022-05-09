#include <iostream>

#include "row/Row.h"
#include "matrix/Matrix.h"

int main()
{
    std::vector<std::vector<double>> v;

    for (int i = 0; i < 4; ++i)
    {
        std::vector<double> row;

        for (int j = 0; j < 5; ++j)
            row.push_back(j + i * 5);

        v.push_back(row);
    }

    Matrix mat(v, 4);

    std::cout << mat << '\n';
    std::cout << mat * mat.T() << "\n";
}

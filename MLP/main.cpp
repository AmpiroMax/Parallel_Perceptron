#include <iostream>

#include "gstring/GString.h"
#include "matrix/Matrix.h"

int main()
{
    std::vector<std::vector<double>> vector;

    for (size_t i = 0; i < 3; ++i)
    {
        std::vector<double> line;

        for (size_t j = 0; j < 4; ++j)
            line.push_back(i + j + 1);

        vector.push_back(line);
    }

    Matrix mat(vector);
    GString str({1, 2, 3, 4});

    std::cout << mat << '\n';

    std::cout << str + mat << '\n';
}

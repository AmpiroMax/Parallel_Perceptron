#include <iostream>
#include <vector>

#include "matrix/Matrix.h"

using std::size_t;

int main()
{
    std::vector<std::vector<double>> vect(1, {1, 2, 3});

    Matrix vector(vect, 1, AlgorithmType::Slow);

    std::cout <<  vector * vector.T() << "\n";
}

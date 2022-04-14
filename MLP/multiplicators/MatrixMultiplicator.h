#ifndef MATRIXMULTIPLICATOR_H
#define MATRIXMULTIPLICATOR_H

#include "../constants.h"

class MatrixMultiplicator
{
  public:
    virtual matrix dot(const matrix &A, const matrix &B) = 0;
};

#endif // MATRIXMULTIPLICATOR_H

#ifndef LINEAR_H
#define LINEAR_H
#include "../multiplicators/MatrixMultiplicator.h"
#include "layer.h"

class Linear : public Layer
{
  private:
    matrix W;
    matrix X;
    matrix bias;

  public:
    Linear(size_t in, size_t out, bool bias);
    matrix forward(const matrix &X) override;
    matrix backward(const matrix &grads) override;
};

#endif // LINEAR_H

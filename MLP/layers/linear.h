#ifndef LINEAR_H
#define LINEAR_H
#include "../matrix/matrix.h"
#include "layer.h"

using std::size_t;

class Linear : public Layer
{
  private:
    Matrix W;
    Matrix bias;
    Matrix *mm;

  public:
    Linear(size_t in, size_t out, bool bias, Matrix *_mm);
    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;
};

#endif // LINEAR_H

#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "layer.h"

class SoftMax : public Layer
{
  private:
    matrix X;

  public:
    SoftMax();

    matrix forward(const matrix &_X) override;
    matrix backward(const matrix &grads) override;
};

#endif // SOFTMAX_H

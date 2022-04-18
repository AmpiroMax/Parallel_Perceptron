#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "layer.h"

class SoftMax : public Layer
{
  private:
    Matrix Ans;
    AlgorithmType type;

  public:
    SoftMax(AlgorithmType algType = AlgorithmType::Slow);

    Matrix forward(const Matrix &_X) override;
    Matrix backward(const Matrix &grads) override;
};

#endif // SOFTMAX_H

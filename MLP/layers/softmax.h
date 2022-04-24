#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "layer.h"

class SoftMax : public Layer
{
  private:
    Matrix SM;
    AlgorithmType type;

  public:
    SoftMax(AlgorithmType algType = AlgorithmType::Slow);

    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;
};

#endif // SOFTMAX_H

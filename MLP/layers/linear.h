#ifndef LINEAR_H
#define LINEAR_H
#include "layer.h"

using std::size_t;

class Linear : public Layer
{
  private:
    Matrix W;
    Matrix bias;
    Matrix X;
    AlgorithmType type;

  public:
    Linear(size_t in, size_t out, bool _bias = true, AlgorithmType algType = AlgorithmType::Slow);
    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;
};

#endif // LINEAR_H

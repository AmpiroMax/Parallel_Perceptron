#ifndef LINEAR_H
#define LINEAR_H
#include "layer.h"

using std::size_t;

class Linear : public Layer
{
  private:
    Matrix W;
    Matrix X;
    GString bias;
    Matrix gradW;
    Matrix gradB;

    AlgorithmType type;

  public:
    Linear(size_t in, size_t out, bool _bias = true, AlgorithmType algType = AlgorithmType::Slow);
    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;

    void gradienDescend(double lr);
};

#endif // LINEAR_H

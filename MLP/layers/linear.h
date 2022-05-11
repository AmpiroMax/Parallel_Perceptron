#ifndef LINEAR_H
#define LINEAR_H
#include "layer.h"

using std::size_t;

class Linear : public Layer
{
  private:
    Matrix W;
    Matrix X;
    Row bias;
    Matrix gradW;
    Matrix gradB;

    int nJobs;

  public:
    Linear(size_t in, size_t out, bool _bias = true, int nJobs = 1);
    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;

    void gradienDescend(double lr);
};

#endif // LINEAR_H

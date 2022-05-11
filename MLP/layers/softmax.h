#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "layer.h"

class SoftMax : public Layer
{
  private:
    Matrix SM;
    int nJobs;

  public:
    SoftMax(int nJobs = 1);

    Matrix forward(const Matrix &X) override;
    Matrix backward(const Matrix &grads) override;
};

#endif // SOFTMAX_H

#ifndef SIGMOID_H
#define SIGMOID_H

#include "layer.h"

class Sigmoid : public Layer
{

  private:
    Matrix sigma;
    int nJobs;

  public:
    Sigmoid(int nJobs = 1);
    virtual Matrix forward(const Matrix &X);
    virtual Matrix backward(const Matrix &grads);

  private:
    double sigm(double x);
};

#endif // SIGMOID_H

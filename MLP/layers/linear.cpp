#include "linear.h"

Linear::Linear(size_t in, size_t out, bool _bias, AlgorithmType algType)
    : W(in, out, 0, 1, algType), bias(0, 0, 0, 1, algType), X(0, 0, 0, 1, algType)
{
    type = algType;
    if (_bias)
        bias = Matrix(out, 1, 0, 1, type);
}
Matrix Linear::forward(const Matrix &_X)
{
    X = _X;
    if (bias.shape().first != 0)
        return W * X + bias;
    else
        return W * X;
}
Matrix Linear::backward(const Matrix &grads)
{
    return X.T() * grads;
}

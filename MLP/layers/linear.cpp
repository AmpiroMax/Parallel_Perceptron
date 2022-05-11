#include "linear.h"
#include <iostream>

Linear::Linear(size_t in, size_t out, bool _bias, int _nJobs)
    : W(in, out, _nJobs, FillingType::Randomize),
      X(0, 0, _nJobs, FillingType::Randomize),
      bias(0),
      gradW(0, 0, _nJobs, FillingType::Randomize)
{
    if (_bias)
        bias = Row(out, FillingType::Randomize);
}

/**
 * @brief Linear::forward
 * @param _X                         - Matrix(batch_size, in_features)
 * @return _X * W + bias (если есть) - результат прохода через слой
 */
Matrix Linear::forward(const Matrix &_X)
{
    X = _X;

    if (bias.shape() != 0)
        return X * W + bias;
    else
        return X * W;
}

/**
 * @brief Linear::backward
 * @param grads                       - Matrix(batch_size, out_features)
 * @return Matrix(batch, in_features) - значение производной по входным параметрам
 */
Matrix Linear::backward(const Matrix &grads)
{
    gradW = X.T() * grads;
    gradB = grads;

    return grads * W.T();
}

/// Пересчет весов с данным learning rate
void Linear::gradienDescend(double lr)
{
    W = W - lr * gradW;
    for (int i = 0; i < gradB.shape().first; ++i)
    {
        bias = bias - lr * gradB[i];
    }
}

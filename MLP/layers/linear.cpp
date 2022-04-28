#include "linear.h"
#include <iostream>

Linear::Linear(size_t in, size_t out, bool _bias, AlgorithmType algType)
    : W(in, out, 0, 1, algType), X(0, 0, 0, 1, algType), bias(0), gradW(0, 0, 0, 1, algType)
{
    type = algType;
    if (_bias)
        bias = GString(out, 0);
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
    return grads * W.T();
}

/// Пересчет весов с данным learning rate
void Linear::gradienDescend(double lr)
{
    W = W - lr * gradW;
}

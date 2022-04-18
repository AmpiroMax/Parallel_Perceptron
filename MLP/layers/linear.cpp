#include "linear.h"

Linear::Linear(size_t in, size_t out, bool _bias)
{
    W = matrix(in, std::vector<double>(out, 0));
    if (_bias)
        bias = matrix(out, std::vector<double>(1, 0));
}
matrix Linear::forward(const matrix &_X)
{
    X = _X; // Потенциально долго, возможно стоит хранить указатели на вход
    if (bias.size() != 0)    //
        return W * X + bias; // Необходимо определить сложение
    else
        return W * X;
}
matrix Linear::backward(const matrix &grads)
{
    return X.T() * grads; // Необходимо определить транспонирование
}

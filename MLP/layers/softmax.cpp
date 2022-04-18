#include "softmax.h"
#include <cmath>

SoftMax::SoftMax()
{
}

matrix SoftMax::forward(const matrix &_X)
{
    // возможно есть смысл проверять размер матрицы
    X = _X;
    std::vector<double> divider(_X.size(), 0.0);

    for (int i = 0; i < _X.size(); ++i)
    {
        for (int j = 0; j < _X[0].size(); ++j)
        {
            divider[j] += exp(_X[i][j]);
        }
    }

    matrix ans(_X.size());

    for (int i = 0; i < _X.size(); ++i)
    {
        for (int j = 0; j < _X[0].size(); ++j)
        {
            ans[i][j] = exp(_X[i][j]) / divider[i];
        }
    }

    return ans;
}

matrix SoftMax::backward(const matrix &grads)
{
}

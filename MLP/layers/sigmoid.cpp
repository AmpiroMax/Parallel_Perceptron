#include "sigmoid.h"
#include <cmath>

Sigmoid::Sigmoid(AlgorithmType algType) : Ans(0, 0, 0, 1, algType)
{
    type = algType;
}

Matrix Sigmoid::forward(const Matrix &X)
{
    // Х.shape = {num features, batch_size}
    // Ans.shape = {num features, batch_size}
    if (Ans.shape().first == 0 || Ans.shape().second == 0)
        Ans = Matrix(X.shape().first, X.shape().second, 0, 1, type);

    for (int i = 0; i < Ans.shape().first; ++i)
    {
        for (int j = 0; j < Ans.shape().second; ++j)
        {
            Ans[i][j] = sigm(X[i][j]);
        }
    }
    return Ans;
}

Matrix Sigmoid::backward(const Matrix &grads)
{

    // Градиент сигмоиды имеет формулу
    // ds/dx = s * (1 - s)
    for (int i = 0; i < Ans.shape().first; ++i)
    {
        for (int j = 0; j < Ans.shape().second; ++j)
        {
            // Градиент sigmoid зависит только от переменной,
            // по которой считалось значение самой функции.
            // Поэтому можно не создавать новой матрицы для хранения
            // градиентов, а заменять значение функции на её производную
            Ans[i][j] = Ans[i][j] * (1 - Ans[i][j]);
        }
    }

    return Ans.T() * grads;
}

double Sigmoid::sigm(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

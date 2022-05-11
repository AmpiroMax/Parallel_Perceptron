#include "sigmoid.h"
#include <cmath>

Sigmoid::Sigmoid(int _nJobs) : sigma(0, 0, _nJobs)
{
    nJobs = _nJobs;
}

/**
 * @brief Sigmoid::forward
 * @param X                                 - Matrix(batch_size, num features)
 * @return Matrix(batch_size, num features) - результат применения сигмоиды к каждому
 *                                          - элементу входной матрицы
 */
Matrix Sigmoid::forward(const Matrix &X)
{
    /// sigma.shape = {batch_size, num features}
    if (sigma.shape().first == 0 || sigma.shape().second == 0)
        sigma = Matrix(X.shape().first, X.shape().second, nJobs);

    // std::cout << X.shape().first << " " << X.shape().second << std::endl;

    for (int i = 0; i < sigma.shape().first; ++i)
    {
        for (int j = 0; j < sigma.shape().second; ++j)
        {
            sigma[i][j] = sigm(X[i][j]);
        }
    }
    return sigma;
}
/**
 * @brief Sigmoid::backward
 * @param grads - Matrix(batch_size, num features)
 * @return
 */
Matrix Sigmoid::backward(const Matrix &grads)
{

    // Градиент сигмоиды имеет формулу
    // ds/dx = s * (1 - s)

    for (int i = 0; i < sigma.shape().first; ++i)
    {
        for (int j = 0; j < sigma.shape().second; ++j)
        {
            // Градиент sigmoid зависит только от переменной,
            // по которой считалось значение самой функции.
            // Поэтому можно не создавать новой матрицы для хранения
            // градиентов, а заменять значение функции на её производную
            sigma[i][j] = sigma[i][j] * (1 - sigma[i][j]) * grads[i][j];
        }
    }
    return sigma;
}

double Sigmoid::sigm(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

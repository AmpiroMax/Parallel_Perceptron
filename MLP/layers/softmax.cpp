#include "softmax.h"
#include <cmath>

SoftMax::SoftMax(AlgorithmType algType) : SM(0, 0, 0, 1, algType)
{
    type = algType;
}
/**
 * @brief SoftMax::forward
 * @param X - Matrix(batch_size, num classes)
 * @return
 */
Matrix SoftMax::forward(const Matrix &X)
{
    // Считаем для каждого елемента батча сумму
    // экспонент, стоящую в знаменателе
    std::vector<double> divider(X.shape().first, 0.0);

    for (int i = 0; i < X.shape().first; ++i)
    {
        for (int j = 0; j < X.shape().second; ++j)
        {
            divider[i] += exp(X[i][j]);
        }
    }

    // Результат Softmax сохраняем, т.к. он необходим для подсчёта градиента
    // SM.shape = {batch_size, num classes}
    if (SM.shape().first == 0 || SM.shape().second == 0)
        SM = Matrix(X.shape().first, X.shape().second, 0, 1, type);

    for (int i = 0; i < X.shape().first; ++i)
    {
        for (int j = 0; j < X.shape().second; ++j)
        {
            SM[i][j] = exp(X[i][j]) / divider[i];
        }
    }

    return SM;
}

Matrix SoftMax::backward(const Matrix &_grads)
{
    int batchSize = SM.shape().first;
    int n_classes = SM.shape().second;

    Matrix batchGrad(batchSize, n_classes, 0, 1, type);
    Matrix SoftMGrad(n_classes, n_classes, 0, 1, type);

    // проход по результату SoftMax для каждого
    // элемента батча
    for (int k = 0; k < batchSize; ++k)
    {
        // Подсчет градиента Softmax для к-го элемента батча
        for (int i = 0; i < n_classes; ++i)
        {
            // Диагональные элементы отличны от остальных,
            // имеею зависимость только от диагонального элемента
            // их считаем слегка по другому
            SoftMGrad[i][i] = SM[k][i] * (1 - SM[k][i]);
            for (int j = i + 1; j < n_classes; ++j)
            {
                // Матрица градиента от softmax симметричная
                SoftMGrad[i][j] = -SM[k][i] * SM[k][j];
                SoftMGrad[j][i] = -SM[k][i] * SM[k][j];
            }
        }

        // Значение итогого градиента для к-го элемента батча
        batchGrad[k] = _grads[k] * SoftMGrad;
    }

    return batchGrad;
}

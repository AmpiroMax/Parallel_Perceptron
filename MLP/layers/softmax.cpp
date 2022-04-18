#include "softmax.h"
#include <cmath>

SoftMax::SoftMax(AlgorithmType algType) : Ans(0, 0, 0, 1, algType)
{
    type = algType;
}

Matrix SoftMax::forward(const Matrix &_X)
{
    // _Х.shape = {n classes, batch_size}

    // Считаем для каждого елемента батча сумму
    // экспонент, стоящую в знаменателе
    std::vector<double> divider(_X.shape().second, 0.0);
    for (int i = 0; i < _X.shape().first; ++i)
    {
        for (int j = 0; j < _X.shape().second; ++j)
        {
            divider[j] += exp(_X[i][j]);
        }
    }

    // Результат Softmax сохраняем, т.к. он необходим
    // для подсчёта градиента
    // Ans.shape = {n classes, batch_size}
    Ans = Matrix(_X.shape().first, _X.shape().second, 0, 1, type);

    for (int i = 0; i < _X.shape().first; ++i)
    {
        for (int j = 0; j < _X.shape().second; ++j)
        {
            Ans[i][j] = exp(_X[i][j]) / divider[j];
        }
    }

    return Ans;
}

Matrix SoftMax::backward(const Matrix &grads)
{
    // Итоговый градиент должен быть размеров {n classes, batch_size}.
    // Однако для удобства копирования елементов, хранить будем
    // транспонированную матрицу.
    // Функция вернёт batchGrad.T()

    // batchGrad.shape = {batch_size, n classes}
    Matrix batchGrad(Ans.shape().second, Ans.shape().first, 0, 1, type);
    // SoftMGrad.shape = {n classes, n classes}
    Matrix SoftMGrad(Ans.shape().first, Ans.shape().first, 0, 1, type);

    int batchSize = batchGrad.shape().first;
    int n_classes = SoftMGrad.shape().first;

    // проход по результату SoftMax для каждого
    // элемента батча
    for (int k = 0; k < batchSize; ++k)
    {
        // Подсчет градиента Softmax для отдельного
        // элемента батча
        for (int i = 0; i < n_classes; ++i)
        {
            // Диагональные элементы отличны от остальных
            // их считаем слегка по другому
            SoftMGrad[i][i] = Ans[i][k] * (1 - Ans[i][k]);
            for (int j = i + 1; j < n_classes; ++j)
            {
                // Матрица градиента от softmax симметричная
                SoftMGrad[i][j] = -Ans[i][k] * Ans[j][k];
                SoftMGrad[j][i] = -Ans[i][k] * Ans[j][k];
            }
        }

        // Значение итогого градиента для к-го элемента батча
        batchGrad[k] = SoftMGrad * grads;
    }

    // Возвращаем матрацу градиентов по батчам
    // размером {n classes, batch_size}
    return batchGrad.T();
}

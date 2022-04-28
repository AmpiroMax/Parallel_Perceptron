#include "crossentropy.h"
#include <cmath>

CrossEntropy::CrossEntropy(AlgorithmType algType)
    : truthLabels(0, 0, 0, 1, algType), predictedLabels(0, 0, 0, 1, algType)
{
    type = algType;
}

/**
 * @brief Calculate CrossEntropy value
 *
 * @param predict - Matrix(batch_size, n.classes) predicted logits
 * @param truth - Matrix(batch_size, 1) numbers of truth classes
 * @return loss function value
 */
double CrossEntropy::forward(const Matrix &predict, const Matrix &truth)
{
    truthLabels = truth;
    predictedLabels = predict;
    double rezult = 0.0;

    std::cout << "predict " << predict.shape().first << " " << predict.shape().second << std::endl;
    std::cout << "truth   " << truth.shape().first << " " << truth.shape().second << std::endl;

    for (int i = 0; i < predict.shape().first; ++i)
    {
        rezult += -log(predict[i][truth[i][0]]);
    }

    // Берем среднее значение ошибки по батчу
    rezult /= predict.shape().first;
    return rezult;
}

/**
 * @brief Calculate CrossEntropy backward pass
 *
 * @return Matrix
 */
Matrix CrossEntropy::backward()
{
    Matrix rezult(predictedLabels.shape().first, predictedLabels.shape().second, 0, 1, type);

    /// dL/dx = (-t1/p1, ..., -tn/pn)
    for (int i = 0; i < rezult.shape().first; ++i)
    {
        rezult[i][truthLabels[i][0]] = -1.0 / predictedLabels[i][truthLabels[i][0]];
    }

    return rezult;
}

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
 * @param predict - Matrix(n.classes, batch_size) predicted logits
 * @param truth - Matrix(batch_size, 1) numbers of truth classes
 * @return loss function value
 */
double CrossEntropy::forward(const Matrix &predict, const Matrix &truth)
{
    truthLabels = truth;
    predictedLabels = predict;
    double rezult = 0.0;

    for (int i = 0; i < predict.shape().second; ++i)
    {
        rezult += -log(predict[truth[i]][i]);
    }
    rezult /= predict.shape().second;
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
    for (int i = 0; i < rezult.shape().second; ++i)
    {
        rezult[truthLabels[i]][i] = -1.0 / predictedLabels[truthLabels[i]][i];
    }

    return rezult;
}

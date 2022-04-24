#ifndef CROSSENTROPY_H
#define CROSSENTROPY_H

#include "layer.h"

class CrossEntropy
{
  private:
    Matrix truthLabels;
    Matrix predictedLabels;
    AlgorithmType type;

  public:
    CrossEntropy(AlgorithmType algType = AlgorithmType::Slow);
    double forward(const Matrix &predict, const Matrix &truth);
    Matrix backward();
};

#endif // CROSSENTROPY_H

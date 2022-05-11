#ifndef CROSSENTROPY_H
#define CROSSENTROPY_H

#include "layer.h"

class CrossEntropy
{
  private:
    Matrix truthLabels;
    Matrix predictedLabels;
    int nJobs;

  public:
    CrossEntropy(int nJobs = 1);
    double forward(const Matrix &predict, const Matrix &truth);
    Matrix backward();
};

#endif // CROSSENTROPY_H

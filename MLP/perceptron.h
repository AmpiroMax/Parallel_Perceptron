#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <vector>

#include "layers/linear.h"
#include "layers/sigmoid.h"
#include "layers/softmax.h"

class Perceptron
{
  private:
    std::vector<Linear> layers;
    Sigmoid activation;
    SoftMax softmax;
    double lr;

  public:
    Perceptron(int inFeatures, int numClasses = 10, double learningRate = 1e-5, int layersNum = 3,
               AlgorithmType type = AlgorithmType::Slow);
    Matrix predict(const Matrix &data);
    void backprop(const Matrix &grads);
};

#endif // PERCEPTRON_H

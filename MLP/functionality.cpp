#include <iostream>
#include <vector>

#include "layers/crossentropy.h"
#include "layers/linear.h"
#include "layers/sigmoid.h"
#include "layers/softmax.h"

constexpr int imgSize = 28;

std::vector<Layer> initModel()
{
    AlgorithmType type = AlgorithmType::Slow;
    std::vector<Layer> model;
    Sigmoid activation(type);
    CrossEntropy lossFunction(type);

    /// Input layer
    model.push_back(Linear(imgSize * imgSize, 1024, true, type));
    model.push_back(activation);

    /// Inner layer
    model.push_back(Linear(1024, 1024, true, type));
    model.push_back(activation);

    /// Output layer
    model.push_back(Linear(1024, 10, true, type));
    model.push_back(activation);

    /// Softmax to bring to probability
    model.push_back(SoftMax(type));
}

void trainLoop(std::vector<Layer> &model)
{
    std::vector<double> loss;
}

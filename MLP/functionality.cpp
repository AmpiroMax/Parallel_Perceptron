#include <iostream>
#include <vector>

#include "layers/crossentropy.h"
#include "layers/linear.h"
#include "layers/sigmoid.h"
#include "layers/softmax.h"

constexpr int imgSize = 28;

void trainLoop()
{
    std::vector<Layer> model;
    Sigmoid activation;

    model.push_back(Linear(imgSize * imgSize, 1024));
    model.push_back(activation);

    model.push_back(Linear(1024, 1024));
    model.push_back(activation);

    model.push_back(Linear(1024, 1024));
    model.push_back(activation);

    model.push_back(Linear(1024, 10));
    model.push_back(activation);

    model.push_back(SoftMax());
    model.push_back(CrossEntropy());
}

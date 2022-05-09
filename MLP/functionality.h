#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <vector>

#include "dataloader/dataloader.h"
#include "layers/crossentropy.h"
#include "layers/linear.h"
#include "layers/sigmoid.h"
#include "layers/softmax.h"
#include "perceptron.h"

void testDataloader();

void testLayers();

void clip(Matrix &images);

void normolize(Matrix &images);

std::vector<double> trainLoop(Perceptron &model, AlgorithmType type = AlgorithmType::Slow);

#endif // FUNCTIONALITY_H

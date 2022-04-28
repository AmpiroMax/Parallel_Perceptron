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

void trainLoop(Perceptron model);

void testDataloader();

void testLayers();

#endif // FUNCTIONALITY_H

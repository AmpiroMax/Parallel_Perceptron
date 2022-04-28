#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <vector>

#include "layers/crossentropy.h"
#include "layers/linear.h"
#include "layers/sigmoid.h"
#include "layers/softmax.h"

constexpr int imgSize = 28;

std::vector<Layer> initModel();

void trainLoop(std::vector<Layer> &model);

void testLayers();

#endif // FUNCTIONALITY_H

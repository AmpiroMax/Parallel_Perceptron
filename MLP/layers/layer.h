#ifndef LAYER_H
#define LAYER_H

#include "../constants.h"
#include "../matrix/Matrix.h"

class Layer
{
  public:
    virtual Matrix forward(const Matrix &X) = 0;
    virtual Matrix backward(const Matrix &grads) = 0;
    virtual ~Layer();
};

#endif // LAYER_H

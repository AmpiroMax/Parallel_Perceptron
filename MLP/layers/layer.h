#ifndef LAYER_H
#define LAYER_H

#include "../constants.h"

class Layer
{
  public:
    virtual matrix forward(const matrix &X) = 0;
    virtual matrix backward(const matrix &grads) = 0;
    virtual ~Layer();
};

#endif // LAYER_H

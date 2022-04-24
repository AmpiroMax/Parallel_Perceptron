#ifndef CROSSENTROPY_H
#define CROSSENTROPY_H

#include "layer.h"

class CrossEntropy : public Layer
{
  public:
    CrossEntropy();
    virtual Matrix forward(const Matrix &X);
    virtual Matrix backward(const Matrix &grads);
};

#endif // CROSSENTROPY_H

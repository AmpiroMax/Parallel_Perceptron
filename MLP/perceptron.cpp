#include "perceptron.h"

Perceptron::Perceptron(int inFeatures, int numClasses, double learningRate, int layersNum, AlgorithmType type)
{
    // Инициализация линейных слоёв
    Linear newLayer(inFeatures, 512, true, type);
    layers.push_back(newLayer);

    for (int i = 1; i < layersNum - 1; ++i)
    {
        newLayer = Linear(512, 512, true, type);
        layers.push_back(newLayer);
    }

    newLayer = Linear(512, numClasses, true, type);
    layers.push_back(newLayer);

    // Инициализация дополнительных переменных модели
    activation = Sigmoid(type);
    softmax = SoftMax(type);
    lr = learningRate;
}

Matrix Perceptron::predict(const Matrix &data)
{
    Matrix out = data;

    for (int i = 0; layers.size(); ++i)
    {
        out = activation.forward(layers[i].forward(out));
    }

    return softmax.forward(out);
}

void Perceptron::backprop(const Matrix &grads)
{
    Matrix grad = softmax.backward(grads);

    for (int i = layers.size() - 1; i >= 0; --i)
    {
        grad = activation.backward(grad);
        grad = layers[i].backward(grad);
        layers[i].gradienDescend(lr);
    }
}

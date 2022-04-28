#include "functionality.h"

std::vector<Layer> initModel()
{
    AlgorithmType type = AlgorithmType::Slow;
    std::vector<Layer> model;
    Sigmoid activation(type);
    CrossEntropy lossFunction(type);

    //    /// Input layer
    //    model.push_back(Linear(imgSize * imgSize, 1024, true, type));
    //    model.push_back(activation);

    //    /// Inner layer
    //    model.push_back(Linear(1024, 1024, true, type));
    //    model.push_back(activation);

    //    /// Output layer
    //    model.push_back(Linear(1024, 10, true, type));
    //    model.push_back(activation);

    //    /// Softmax to bring to probability
    //    model.push_back(SoftMax(type));
}

void trainLoop(std::vector<Layer> &model)
{
    std::vector<double> loss;
}

void testLayers()
{
    int in_feat = 2;
    int out_feat = 3;
    int batch = 5;

    Linear l1(in_feat, out_feat);

    // batch, in
    std::vector<std::vector<double>> vec2X({{1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}});
    // batch, out
    std::vector<std::vector<double>> vec2Grads({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    double lr = 1e-3;

    Matrix X(vec2X);
    Matrix grads(vec2Grads);

    Matrix out;
    Matrix back;
    //----------------------------------------------------------
    std::cout << "Linear TEST" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Iteration " << i + 1 << std::endl;
        out = l1.forward(X);
        back = l1.backward(grads);

        std::cout << out << std::endl;
        std::cout << back << std::endl;
        l1.gradienDescend(lr);
    }

    //----------------------------------------------------------
    std::cout << "Sigmoid TEST" << std::endl;
    std::vector<std::vector<double>> vec;
    Matrix mat1;
    Sigmoid sigm;

    for (int i = 0; i <= 5; ++i)
    {
        std::vector<double> tmp;
        for (int j = 0; j <= 10; ++j)
        {
            std::cout << -1.0 + 1.0 * i / 5 + 1.0 * j / 10 << " ";
            tmp.push_back(-1.0 + 1.0 * i / 5 + 1.0 * j / 10);
        }
        vec.push_back(tmp);
        std::cout << std::endl;
    }
    mat1 = Matrix(vec);
    std::cout << sigm.forward(mat1) << std::endl;
    std::cout << std::endl;
    std::cout << sigm.backward(mat1) << std::endl;

    //----------------------------------------------------------
    std::cout << "SoftMax CrossEntropy TEST" << std::endl;
    std::vector<std::vector<double>> vec2({{0, 1, 0}, {10, 1, 1}, {10, 1, 10}, {2, 1, 1}});
    std::vector<std::vector<double>> labels({{1}, {0}, {1}, {2}});

    Matrix mat2(vec2);
    Matrix trueLabels(labels);
    Matrix grad;

    CrossEntropy CE;
    SoftMax SM;

    Matrix logits = SM.forward(mat2);
    double loss = CE.forward(logits, trueLabels);

    std::cout << logits << std::endl;
    std::cout << loss << std::endl;

    grad = CE.backward();

    std::cout << grad << std::endl;

    grad = SM.backward(grad);

    std::cout << grad << std::endl;
    //    std::cout <<  << std::endl;
}

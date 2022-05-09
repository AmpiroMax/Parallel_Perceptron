#include "functionality.h"
#include <chrono>
#include <cmath>

void testDataloader()
{
    std::string path = "C:/Max/Progra/Parallel_Perceptron/MNIST_data/MNIST/train";
    Dataloader trainLoader(path);

    int batchSize = 10;

    std::vector<std::vector<std::vector<double>>> datasetImages = trainLoader.getImages(batchSize);
    std::vector<std::vector<double>> datasetLabels = trainLoader.getLabels(batchSize);

    for (int batchNum = 0; batchNum < 3; ++batchNum)
    {
        Matrix images(datasetImages[batchNum]);

        std::cout << "-------------------------------------------" << std::endl;

        for (int i = 0; i < batchSize; ++i)
        {
            std::cout << "CLASS: " << datasetLabels[batchNum][i] << std::endl;
            std::cout << "IMAGE: " << std::endl;

            for (int j = 0; j < IMAGE_SIZE * IMAGE_SIZE; ++j)
            {
                if (j % IMAGE_SIZE == 0)
                    std::cout << std::endl;
                std::cout << char(images[i][j]) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void testLayers()
{
    int in_feat = 2;
    int out_feat = 3;

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

void clip(Matrix &images)
{
    double min = 255;
    double max = 0.1;

    for (int i = 0; i < images.shape().first; ++i)
    {
        for (int j = 0; j < images.shape().second; ++j)
        {
            if (images[i][j] > max)
                max = images[i][j];
            if (images[i][j] < min)
                min = images[i][j];
        }
    }
    for (int i = 0; i < images.shape().first; ++i)
    {
        for (int j = 0; j < images.shape().second; ++j)
        {
            images[i][j] = (images[i][j] - min) / (max - min);
        }
    }
}

void normolize(Matrix &images)
{
    double mean = 255;
    double std = 0.1;

    for (int i = 0; i < images.shape().first; ++i)
    {
        for (int j = 0; j < images.shape().second; ++j)
        {
            mean += images[i][j];
        }
        mean = mean / images.shape().first / images.shape().second;
        for (int j = 0; j < images.shape().second; ++j)
        {
            std += (images[i][j] - mean) * (images[i][j] - mean);
        }
        std /= (images.shape().first * images.shape().second - 1);
        std = sqrt(std);
        for (int j = 0; j < images.shape().second; ++j)
        {
            images[i][j] = (images[i][j] - mean) / std;
        }
    }

    //    double mean = 255;
    //    double std = 0.1;

    //    for (int i = 0; i < images.shape().first; ++i)
    //    {
    //        for (int j = 0; j < images.shape().second; ++j)
    //        {
    //            mean += images[i][j];
    //        }
    //    }
    //    mean = mean / images.shape().first / images.shape().second;

    //    for (int i = 0; i < images.shape().first; ++i)
    //    {
    //        for (int j = 0; j < images.shape().second; ++j)
    //        {
    //            std += (images[i][j] - mean) * (images[i][j] - mean);
    //        }
    //    }

    //    std /= (images.shape().first * images.shape().second - 1);
    //    std = sqrt(std);

    //    for (int i = 0; i < images.shape().first; ++i)
    //    {
    //        for (int j = 0; j < images.shape().second; ++j)
    //        {
    //            images[i][j] = (images[i][j] - mean) / std;
    //        }
    //    }
}

std::vector<double> trainLoop(Perceptron &model, AlgorithmType type)
{
    int batchSize = 128;
    int epochs = 20;
    std::vector<double> loss;
    CrossEntropy lossFunk(type);

    std::string trainPath = "C:/Max/Progra/Parallel_Perceptron/MNIST_data/MNIST/train";
    std::string testPath = "C:/Max/Progra/Parallel_Perceptron/MNIST_data/MNIST/test";

    std::cout << "-------Initializing Loaders-------" << std::endl;
    Dataloader trainLoader(trainPath);
    Dataloader testLoader(testPath);
    std::cout << "-------Loaders are initialized----" << std::endl;

    std::cout << "-------Initializing Batches-------" << std::endl;
    std::vector<std::vector<std::vector<double>>> trainImages = trainLoader.getImages(batchSize);
    std::vector<std::vector<double>> trainLabels = trainLoader.getLabels(batchSize);

    std::vector<std::vector<std::vector<double>>> testImages = trainLoader.getImages(batchSize);
    std::vector<std::vector<double>> testLabels = trainLoader.getLabels(batchSize);
    std::cout << "-------Batches are initialized----" << std::endl;

    int limit = 100;

    auto totalBegin = std::chrono::steady_clock::now();

    for (int epoch = 0; epoch < epochs; ++epoch)
    {
        std::cout << "Epoch #" << epoch + 1 << "/" << epochs << std::endl;
        double meanLoss = 0.0;

        auto epochBegin = std::chrono::steady_clock::now();

        for (int batchNum = 0; (batchNum < trainImages.size() && batchNum < limit); ++batchNum)
        {
            double currLoss;

            Matrix images(trainImages[batchNum], 1, type);
            Matrix labels(GString(trainLabels[batchNum]), 1, type);
            Matrix prediction;
            normolize(images);

            // auto begin = std::chrono::steady_clock::now();

            prediction = model.predict(images);
            currLoss = lossFunk.forward(prediction, labels);
            Matrix grad = lossFunk.backward();
            model.backprop(grad);

            // auto end = std::chrono::steady_clock::now();
            // auto modelWorkTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            // std::cout << modelWorkTime.count() << " ms, ";

            meanLoss += currLoss;
            if ((batchNum + 1) % 10 == 0)
                std::cout << "[" << batchNum + 1 << "/" << limit << "] " << meanLoss / (batchNum + 1) << std::endl;
        }

        auto epochEnd = std::chrono::steady_clock::now();
        auto epochWorkTime = std::chrono::duration_cast<std::chrono::seconds>(epochEnd - epochBegin);
        std::cout << "Epoch time: " << epochWorkTime.count() << " s" << std::endl;

        loss.push_back(meanLoss / (limit > trainImages.size() ? trainImages.size() : limit));
        std::cout << std::endl;
    }

    auto totalEnd = std::chrono::steady_clock::now();
    auto epochWorkTime = std::chrono::duration_cast<std::chrono::minutes>(totalEnd - totalBegin);
    std::cout << "Total time: " << epochWorkTime.count() << " minutes" << std::endl;

    return loss;
}

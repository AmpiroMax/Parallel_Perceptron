#include "dataloader.h"
#include "../constants.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief Переводит число из big endian в little endian
 * @param i - число, которое будет обращаться
 * @return перевёрнытый int
 */
int Dataloader::reverseInt(int i)
{
    unsigned char c1, c2, c3, c4;
    c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
};

/**
 * @brief Чтение изображений MNIST из бинарного файла
 * @param full_path        - расположение файла для чтения
 * @param number_of_images - число изображений, которое считалось
 * @param image_size       - размер изображений, лежавших в файле
 * @return матрицу uchar   - считынне изображения
 *
 * Считывает изображения и созраняет их в матрицу uchar**. Каждое изображение
 * кодируется положительным целым числом от 0 до 255, представленное char.
 */
char **Dataloader::readMNISTImages(std::string fullPath, int &numberOfImages, int &imageSize)
{
    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open())
    {
        int magic_number = 0, n_rows = 0, n_cols = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2051)
            throw std::runtime_error("Invalid MNIST image file!");

        file.read((char *)&numberOfImages, sizeof(numberOfImages)), numberOfImages = reverseInt(numberOfImages);
        file.read((char *)&n_rows, sizeof(n_rows)), n_rows = reverseInt(n_rows);
        file.read((char *)&n_cols, sizeof(n_cols)), n_cols = reverseInt(n_cols);

        imageSize = n_rows * n_cols;

        char **_dataset = new char *[numberOfImages];
        for (int i = 0; i < numberOfImages; i++)
        {
            _dataset[i] = new char[imageSize];
            file.read((char *)_dataset[i], imageSize);
        }
        return _dataset;
    }
    else
    {
        throw std::runtime_error("Cannot open file `" + fullPath + "`!");
    }
}

/**
 * @brief Чтение лейблов картинок MNIST из бинарного файла
 * @param full_path        - расположение файла для чтения
 * @param number_of_labels - число считанных label
 * @return массив uchar*   - массив из значений labels для
 *                           соответствующей картинки
 */
char *Dataloader::readMNISTLabels(std::string fullPath, int &numberOfLabels)
{
    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open())
    {
        int magic_number = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2049)
            throw std::runtime_error("Invalid MNIST label file!");

        file.read((char *)&numberOfLabels, sizeof(numberOfLabels)), numberOfLabels = reverseInt(numberOfLabels);

        char *_dataset = new char[numberOfLabels];
        for (int i = 0; i < numberOfLabels; i++)
        {
            file.read((char *)&_dataset[i], 1);
        }
        return _dataset;
    }
    else
    {
        throw std::runtime_error("Unable to open file `" + fullPath + "`!");
    }
}

void Dataloader::convertData(char *rawLabels, char **rawImages)
{
    for (int i = 0; i < numOfLabels; ++i)
    {
        std::vector<double> tmp;
        for (int j = 0; j < imgSize; ++j)
        {
            tmp.push_back((double)(rawImages[i][j]));
        }

        labels.push_back((double)(rawLabels[i]));
        images.push_back(tmp);
    }
}

Dataloader::Dataloader(std::string path)
{
    char *rawLabels = readMNISTLabels(path + "/labels", numOfLabels);
    char **rawImages = readMNISTImages(path + "/images", numOfImages, imgSize);

    std::cout << "Num of labels, images, imgSize: " << numOfLabels << " " << numOfImages << " " << imgSize << std::endl;

    if (numOfImages != numOfLabels)
    {
        delete[] rawLabels;
        delete[] rawImages;
        throw std::runtime_error("Images and labels number are not the same");
    }
    convertData(rawLabels, rawImages);

    delete[] rawLabels;
    delete[] rawImages;
}

std::vector<std::vector<std::vector<double>>> Dataloader::getImages(int batchSize)
{
    std::vector<std::vector<std::vector<double>>> imageBatches;

    for (int i = 0; i < (images.size() / batchSize); ++i)
    {
        std::vector<std::vector<double>> tmp;
        for (int j = 0; j < batchSize; ++j)
        {
            tmp.push_back(images[i * batchSize + j]);
        }
        imageBatches.push_back(tmp);
    }

    return imageBatches;
}

std::vector<std::vector<int>> Dataloader::getLabels(int batchSize)
{
    std::vector<std::vector<int>> labelBatches;

    for (int i = 0; i < (labels.size() / batchSize); ++i)
    {
        std::vector<int> tmp;
        for (int j = 0; j < batchSize; ++j)
        {
            tmp.push_back(labels[i * batchSize + j]);
        }
        labelBatches.push_back(tmp);
    }

    return labelBatches;
}

void Dataloader::printData()
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << std::endl;
        std::cout << labels[i] << std::endl;
        for (int j = 0; j < imgSize; ++j)
        {
            if (j % IMAGE_SIZE == 0)
                std::cout << std::endl;
            std::cout << char(images[i][j]) << " ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

#ifndef DATALOADER_H
#define DATALOADER_H

#include <fstream>
#include <vector>

typedef unsigned char uchar;

class Dataloader
{
  private:
    int numOfImages;
    int numOfLabels;
    int imgSize;

    std::vector<double> labels;
    std::vector<std::vector<double>> images;

    int reverseInt(int i);
    uchar *readMNISTLabels(const std::string &fullPath, int &numberOfLabels);
    uchar **readMNISTImages(const std::string &fullPath, int &numberOfImages, int &imageSize);
    void convertData(uchar *rawLabels, uchar **rawImages);

  public:
    Dataloader(std::string path);
    std::vector<std::vector<std::vector<double>>> getImages(int batchSize);
    std::vector<std::vector<double>> getLabels(int batchSize);

    void printData();
};

#endif // DATALOADER_H

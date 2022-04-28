#ifndef DATALOADER_H
#define DATALOADER_H

#include <fstream>
#include <vector>

class Dataloader
{
  private:
    int numOfImages;
    int numOfLabels;
    int imgSize;

    std::vector<int> labels;
    std::vector<std::vector<double>> images;

    int reverseInt(int i);
    char *readMNISTLabels(std::string fullPath, int &numberOfLabels);
    char **readMNISTImages(std::string fullPath, int &numberOfImages, int &imageSize);
    void convertData(char *rawLabels, char **rawImages);

  public:
    Dataloader(std::string path);
    std::vector<std::vector<std::vector<double>>> getImages(int batchSize);
    std::vector<std::vector<int>> getLabels(int batchSize);

    void printData();
};

#endif // DATALOADER_H

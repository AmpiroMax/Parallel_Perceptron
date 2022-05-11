#include <iostream>

#include "functionality.h"
#include "perceptron.h"

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

/*

▒▒▒▒▒▒▒▒█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▒▒▒▒▒▒
▒▒▒▒▒▒▒█░▒▒▒▒▒▒▒▓▒▒▓▒▒▒▒▒▒▒░█▒▒▒▒▒
▒▒▒▒▒▒▒█░▒▒▓▒▒▒▒▒▒▒▒▒▄▄▒▓▒▒░█░▄▄▒▒
▒▒▄▀▀▄▄█░▒▒▒▒▒▒▓▒▒▒▒█░░▀▄▄▄▄▄▀░░█▒
▒▒█░░░░█░▒▒▒▒▒▒▒▒▒▒▒█░░░░░░░░░░░█▒
▒▒▒▀▀▄▄█░▒▒▒▒▓▒▒▒▓▒█░░░█▒░░░░█▒░░█
▒▒▒▒▒▒▒█░▒▓▒▒▒▒▓▒▒▒█░░░░░░░▀░░░░░█
▒▒▒▒▒▄▄█░▒▒▒▓▒▒▒▒▒▒▒█░░█▄▄█▄▄█░░█▒
▒▒▒▒█░░░█▄▄▄▄▄▄▄▄▄▄█░█▄▄▄▄▄▄▄▄▄█▒▒
▒▒▒▒█▄▄█░░█▄▄█░░░░░░█▄▄█░░█▄▄█▒▒▒▒

*/

int main()
{
    int nJobs = 5;
    Perceptron model(784, 10, 0.00015, 3, nJobs);
    std::vector<double> loss = trainLoop(model, nJobs);
    plt::plot(loss);
    plt::show();
    return 0;
}

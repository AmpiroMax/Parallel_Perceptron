#include <iostream>

#include "functionality.h"
#include "gstring/GString.h"
#include "matrix/Matrix.h"
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
    Perceptron model(784, 10, 0.0001, 3);
    std::vector<double> loss = trainLoop(model);
    plt::plot(loss);
    plt::show();
    return 0;
}

cmake_minimum_required(VERSION 3.5)

project(MLP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp

    layers/linear.cpp
    layers/softmax.cpp
    layers/sigmoid.cpp
    layers/crossentropy.cpp
    perceptron.cpp

    functionality.cpp
    dataloader/dataloader.cpp

    matrix/matrix.cpp
    gstring/GString.cpp
)


set(HEADERS
    layers/layer.h
    layers/linear.h
    layers/softmax.h
    layers/sigmoid.h
    layers/crossentropy.h
    perceptron.h

    functionality.h
    dataloader/dataloader.h

    constants.h
    errors/errors.h
    gstring/GString.h
    matrix/Matrix.h
)

add_executable(
    MLP
    ${SOURCES}
    ${HEADERS}
)

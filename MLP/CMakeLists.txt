cmake_minimum_required(VERSION 3.5)

project(MLP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    layers/linear.cpp
    layers/softmax.cpp
    layers/sigmoid.cpp
    matrix/matrix.cpp
    layers/crossentropy.cpp
    functionality.cpp
    dataloader/dataloader.cpp
)

set(HEADERS
    constants.h
    layers/layer.h
    matrix/Matrix.h
    dataloader/dataloader.h

    layers/linear.h
    layers/softmax.h
    layers/sigmoid.h
    layers/crossentropy.h

)

add_executable(
    MLP
    ${SOURCES}
    ${HEADERS}
)

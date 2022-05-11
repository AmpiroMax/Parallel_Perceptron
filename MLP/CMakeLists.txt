cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(MLP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})


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
    row/Row.cpp
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
    row/Row.h
    matrix/Matrix.h

    matplotlibcpp.h
)

add_executable(
    MLP
    ${SOURCES}
    ${HEADERS}
)


# link python and numpy
target_link_libraries(
    MLP
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)




#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <utility>
#include <vector>

using std::size_t;

enum class AlgorithmType {Slow, Fast};

class Matrix
{
private:

    std::vector<std::vector<double>> mat;
    size_t n_jobs;
    AlgorithmType type;

    const Matrix __dotSlow(const Matrix& rhs) const;

public:

    explicit Matrix(size_t n, size_t m, double fill, size_t n_jobs, AlgorithmType type);
    explicit Matrix(size_t n, size_t m, size_t n_jobs, AlgorithmType type);
    explicit Matrix(std::vector<std::vector<double>>& table, size_t n_jobs, AlgorithmType type);

    friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
    friend const Matrix operator* (double num, const Matrix& matrix);
    friend const Matrix operator* (const Matrix& matrix, double num);
    friend const Matrix operator* (const Matrix& lhs, const Matrix& rhs);
    friend const Matrix operator+ (double num, const Matrix& matrix);
    friend const Matrix operator+ (const Matrix& matrix, double num);
    friend const Matrix operator- (double num, const Matrix& matrix);
    friend const Matrix operator- (const Matrix& matrix, double num);

    std::pair<size_t, size_t> shape() const;
    Matrix T() const;
};

#endif // MATRIX_H

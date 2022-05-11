#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <utility>
#include <vector>

#include "../constants.h"
#include "../row/Row.h"

using std::size_t;

class Matrix
{
private:

    std::vector<Row> _mat;
    size_t _n_jobs;

    void _checkArguments(const Matrix& rhs) const;
    const Matrix _dotSlow(const Matrix& rhs) const;
    void _dotThread(const Matrix& rhs, Matrix& product, int start, int finish) const;
    const Matrix _dotFast(const Matrix& rhs) const;

public:

    Matrix() = default;
    explicit Matrix(size_t n, size_t m, size_t n_jobs=1, FillingType type=FillingType::UseFill, double fill=0);
    explicit Matrix(std::pair<size_t, size_t> shape, size_t n_jobs=1,
                    FillingType type=FillingType::UseFill, double fill=0);
    explicit Matrix(const std::vector<Row>& v, size_t n_jobs=1);
    explicit Matrix(const std::vector<std::vector<double>>& v, size_t n_jobs=1);
    explicit Matrix(const Row& row, size_t n_jobs=1);

    friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>> (std::istream& is, Matrix& matrix);

    friend const Matrix operator+ (const Matrix& matrix, double num);
    friend const Matrix operator+ (double num, const Matrix& matrix);
    friend const Matrix operator+ (const Matrix& lhs, const Matrix& rhs);
    friend const Matrix operator+ (const Matrix& matrix, const Row& str);
    friend const Matrix operator+ (const Row& str, const Matrix& matrix);

    friend const Matrix operator* (double num, const Matrix& matrix);
    friend const Matrix operator* (const Matrix& matrix, double num);
    friend const Matrix operator* (const Matrix& lhs, const Matrix& rhs);
    friend const Matrix operator* (const Matrix& lhs, const Row& rhs);
    friend const Row operator* (const Row& lhs, const Matrix& rhs);

    friend const Matrix operator- (double num, const Matrix& matrix);
    friend const Matrix operator- (const Matrix& matrix, double num);
    friend const Matrix operator- (const Matrix& lhs, const Matrix& rhs);

    friend const Matrix operator/ (const Matrix& matrix, double num);
    friend const Matrix operator/ (double num, const Matrix& matrix);

    Matrix& operator= (const Matrix& matrix);

    const Row& operator[] (size_t i) const;
    Row& operator[] (size_t i);

    std::pair<size_t, size_t> shape() const;
    Matrix T() const;
};

#endif // MATRIX_H

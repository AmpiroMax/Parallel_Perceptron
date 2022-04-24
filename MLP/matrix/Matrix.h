#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <utility>
#include <vector>

#include "../gstring/GString.h"

using std::size_t;

enum class AlgorithmType {Slow, Fast};

class Matrix
{
private:

    std::vector<GString> _mat;
    size_t _n_jobs;
    AlgorithmType _type;

    const Matrix __dotSlow(const Matrix& rhs) const;

public:

    Matrix() = default;
    explicit Matrix(size_t n, size_t m);
    explicit Matrix(size_t n, size_t m, size_t n_jobs, AlgorithmType type);
    explicit Matrix(size_t n, size_t m, double fill, size_t n_jobs, AlgorithmType type);
    explicit Matrix(std::pair<size_t, size_t> shape);
    explicit Matrix(std::pair<size_t, size_t> shape, size_t n_jobs, AlgorithmType type);
    explicit Matrix(std::pair<size_t, size_t> shape, double fill, size_t n_jobs, AlgorithmType type);
    explicit Matrix(const std::vector<GString>& v, size_t n_jobs, AlgorithmType type);
    explicit Matrix(const std::vector<GString>& v);
    explicit Matrix(const std::vector<std::vector<double>>& v, size_t n_jobs, AlgorithmType type);
    explicit Matrix(const std::vector<std::vector<double>>& v);
    explicit Matrix(const GString& str, size_t n_jobs, AlgorithmType type);
    explicit Matrix(const GString& str);

    friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>> (std::istream& is, Matrix& matrix);

    friend const Matrix operator+ (const Matrix& matrix, double num);
    friend const Matrix operator+ (double num, const Matrix& matrix);
    friend const Matrix operator+ (const Matrix& lhs, const Matrix& rhs);
    friend const Matrix operator+ (const Matrix& matrix, const GString& str);
    friend const Matrix operator+ (const GString& str, const Matrix& matrix);

    friend const Matrix operator* (double num, const Matrix& matrix);
    friend const Matrix operator* (const Matrix& matrix, double num);
    friend const Matrix operator* (const Matrix& lhs, const Matrix& rhs);
    friend const Matrix operator* (const Matrix& lhs, const GString& rhs);
    friend const GString operator* (const GString& lhs, const Matrix& rhs);

    friend const Matrix operator- (double num, const Matrix& matrix);
    friend const Matrix operator- (const Matrix& matrix, double num);
    friend const Matrix operator- (const Matrix& lhs, const Matrix& rhs);

    friend const Matrix operator/ (const Matrix& matrix, double num);
    friend const Matrix operator/ (double num, const Matrix& matrix);

    Matrix& operator= (const Matrix& matrix);

    const GString& operator[] (size_t i) const;
    GString& operator[] (size_t i);

    std::pair<size_t, size_t> shape() const;
    Matrix T() const;
};

#endif // MATRIX_H

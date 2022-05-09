#include <algorithm>
#include <thread>
#include <random>
#include <cmath>

#include "Matrix.h"
#include "../errors/errors.h"

//----------------------------------------------------------------------------------------------------------------------
// Блок конструкторов
//----------------------------------------------------------------------------------------------------------------------

Matrix::Matrix(size_t n, size_t m, size_t n_jobs, FillingType type, double fill):
    _n_jobs(n_jobs)
{
    if (type == FillingType::UseFill)
        _mat = std::vector<Row>(n, Row(m, type, fill));

    else
    {
        _mat = std::vector<Row>(n, Row(m, FillingType::UseFill, 0));

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<double> d;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                _mat[i][j] = d(gen);
    }
}

Matrix::Matrix(std::pair<size_t, size_t> shape, size_t n_jobs, FillingType type, double fill):
    Matrix(shape.first, shape.second, n_jobs, type, fill) {}

Matrix::Matrix(const std::vector<Row>& v, size_t n_jobs):
    _mat(v), _n_jobs(n_jobs) {}

Matrix::Matrix(const std::vector<std::vector<double>> &v, size_t n_jobs):
    _n_jobs(n_jobs)
{
    _mat = std::vector<Row>(v.size());

    for (size_t i = 0; i < _mat.size(); ++i)
        _mat[i] = Row(v[i]);
}

Matrix::Matrix(const Row &row, size_t n_jobs):
        _mat(1, row), _n_jobs(n_jobs) {}

//----------------------------------------------------------------------------------------------------------------------
// Блок перегруженных операторов
//----------------------------------------------------------------------------------------------------------------------

// Ввод / вывод
std::ostream& operator<< (std::ostream& os, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.shape().first; ++i)
        os << matrix._mat[i] << "\n";

    return os;
}


std::istream& operator>> (std::istream& is, Matrix& matrix)
{
    for (size_t i = 0; i < matrix.shape().first; ++i)
        is >> matrix._mat[i];

    return is;
}

// Оператор сложения
const Matrix operator+ (const Matrix& matrix, double num)
{
    Matrix sum(matrix);

    for (size_t i = 0; i < matrix.shape().first; ++i)
        sum._mat[i] = sum._mat[i] + num;

    return sum;
}


const Matrix operator+ (double num, const Matrix& matrix)
{
    return matrix + num;
}


const Matrix operator+ (const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.shape() != rhs.shape())
        throw DimensionsError();

    else if (lhs._n_jobs != rhs._n_jobs)
        throw MultiprocessingError();

    Matrix sum(lhs);

    for (size_t i = 0; i < sum.shape().first; ++i)
        sum._mat[i] = sum._mat[i] + rhs._mat[i];

    return sum;
}


const Matrix operator+ (const Matrix& matrix, const Row& row)
{
    if (matrix.shape().second != row.shape())
        throw DimensionsError();

    Matrix sum(matrix);

    for (size_t i = 0; i < sum.shape().first; ++i)
        sum._mat[i] = sum._mat[i] + row;

    return sum;
}

const Matrix operator+ (const Row& row, const Matrix& matrix)
{
    return matrix + row;
}

// Оператор умножения
const Matrix operator* (const Matrix& matrix, double num)
{
    Matrix product(matrix);

    for (size_t i = 0; i < product.shape().first; ++i)
        product._mat[i] = product._mat[i] * num;

    return product;
}


const Matrix operator* (double num, const Matrix& matrix)
{
    return matrix * num;
}


const Matrix operator* (const Matrix& lhs, const Matrix& rhs)
{
    if (lhs._n_jobs == 1)
        return lhs._dotSlow(rhs);

    if (lhs._n_jobs > 1)
        return lhs._dotFast(rhs);

    return lhs * 0;
}


const Matrix operator* (const Matrix& lhs, const Row& rhs)
{
    Matrix rhs_mat(rhs, lhs._n_jobs);

    if (lhs._n_jobs == 1)
        return lhs._dotSlow(rhs_mat);

    return lhs * 0;
}


const Row operator* (const Row& lhs, const Matrix& rhs)
{
    Matrix lhs_mat(lhs, rhs._n_jobs);

    if (lhs_mat._n_jobs == 1)
        return lhs_mat._dotSlow(rhs)[0];

    return lhs * 0;
}

// Оператор вычетания
const Matrix operator- (double num, const Matrix& matrix)
{
    return -1 * matrix + num;
}


const Matrix operator- (const Matrix& matrix, double num)
{
    return matrix + (-num);
}


const Matrix operator- (const Matrix& lhs, const Matrix& rhs)
{
    return lhs + (-1) * rhs;
}

// Оператор деления
const Matrix operator/ (const Matrix& matrix, double num)
{
    Matrix divided(matrix);

    for (size_t i = 0; i < divided.shape().first; ++i)
        divided._mat[i] = divided._mat[i] / num;

    return divided;
}


const Matrix operator/ (double num, const Matrix& matrix)
{
    Matrix divided(matrix);

    for (size_t i = 0; i < matrix.shape().first; ++i)
        divided._mat[i] = num / divided._mat[i];

    return divided;
}

// Оператор присваивания
Matrix& Matrix::operator= (const Matrix &matrix)
{
    if (&matrix == this)
        return *this;

    _mat = matrix._mat;
    _n_jobs = matrix._n_jobs;

    return *this;
}

// Оператор доступа к элементам
const Row& Matrix::operator[](size_t i) const
{
    return _mat[i];
}


Row& Matrix::operator[](size_t i)
{
    return _mat[i];
}

//----------------------------------------------------------------------------------------------------------------------
// Блок публичных методов
//----------------------------------------------------------------------------------------------------------------------

std::pair<size_t, size_t> Matrix::shape() const
/*
 * Возвращает пару {количество строк, количество столбцов}
 */
{
    if (_mat.empty())
        return {0, 0};

    return {_mat.size(), _mat[0].shape()};
}


Matrix Matrix::T() const
/*
 * Транспонирует матрицу
 *
 * Возвращает транспонированную матрицу
 */
{
    Matrix transposed(shape().second, shape().first, _n_jobs);

    for (size_t i = 0; i < shape().first; ++i)
        for (size_t j = 0; j < shape().second; ++j)
            transposed._mat[j][i] = _mat[i][j];

    return transposed;
}

//----------------------------------------------------------------------------------------------------------------------
// Блок приватных методов
//----------------------------------------------------------------------------------------------------------------------

void Matrix::_checkArguments(const Matrix &rhs) const
{
    if (shape().second != rhs.shape().first)
        throw DimensionsError();

    else if (_n_jobs != rhs._n_jobs)
        throw MultiprocessingError();
}


const Matrix Matrix::_dotSlow(const Matrix &rhs) const
{
    _checkArguments(rhs);

    Matrix product(shape().first, rhs.shape().second, _n_jobs);

    for (size_t i = 0; i < shape().first; ++i)
    {
        for (size_t j = 0; j < shape().second; ++j)
            product[i] = product[i] + _mat[i][j] * rhs[j];
    }

    return product;
}

void Matrix::_dotThread(const Matrix& rhs, Matrix& product, int start, int finish) const
{
    for (int i = start; i < finish; ++i)
        for (size_t j = 0; j < shape().second; ++j)
            product[i] = product[i] + _mat[i][j] * rhs[j];
}


const Matrix Matrix::_dotFast(const Matrix &rhs) const
{
    _checkArguments(rhs);

    Matrix product(shape().first, rhs.shape().second, _n_jobs);
    std::vector<std::thread> threads;

    int step = static_cast<int>(shape().first / _n_jobs) + 1;

    for (int i = 0; i < _n_jobs; ++i)
    {
        int start = i * step, finish = (i + 1) * step;

        if (finish > shape().first)
            finish = shape().first;

        threads.push_back(std::thread(&Matrix::_dotThread, this, std::cref(rhs), std::ref(product), start, finish));
    }

    for (int i = 0; i < threads.size(); ++i)
        threads[i].join();

    return product;
}

#include "Matrix.h"
#include "../errors/errors.h"

//----------------------------------------------------------------------------------------------------------------------
// Блок конструкторов
//----------------------------------------------------------------------------------------------------------------------

Matrix::Matrix(size_t n, size_t m, double fill, size_t n_jobs, AlgorithmType type):
    _mat(n, GString(m, fill)), _n_jobs(n_jobs), _type(type) {}

Matrix::Matrix(size_t n, size_t m, size_t n_jobs, AlgorithmType type):
    Matrix(n, m, 0, n_jobs, type) {}

Matrix::Matrix(size_t n, size_t m):
    Matrix(n, m, 0, 1, AlgorithmType::Slow) {}

Matrix::Matrix(std::pair<size_t, size_t> shape, double fill, size_t n_jobs, AlgorithmType type):
    Matrix(shape.first, shape.second, fill, n_jobs, type) {}

Matrix::Matrix(std::pair<size_t, size_t> shape, size_t n_jobs, AlgorithmType type):
    Matrix(shape.first, shape.second, 0, n_jobs, type) {}

Matrix::Matrix(std::pair<size_t, size_t> shape):
    Matrix(shape.first, shape.second, 0, 1, AlgorithmType::Slow) {}

Matrix::Matrix(const std::vector<GString>& v, size_t n_jobs, AlgorithmType type):
    _mat(v), _n_jobs(n_jobs), _type(type) {}

Matrix::Matrix(const std::vector<GString> &v):
    Matrix(v, 1, AlgorithmType::Slow) {}

Matrix::Matrix(const std::vector<std::vector<double>> &v, size_t n_jobs, AlgorithmType type):
    _n_jobs(n_jobs), _type(type)
{
    _mat = std::vector<GString>(v.size());

    for (size_t i = 0; i < _mat.size(); ++i)
        _mat[i] = GString(v[i]);
}

Matrix::Matrix(const std::vector<std::vector<double>> &v):
    Matrix(v, 1, AlgorithmType::Slow) {}

Matrix::Matrix(const GString &str, size_t n_jobs, AlgorithmType type):
    _mat(1, str), _n_jobs(n_jobs), _type(type) {}

Matrix::Matrix(const GString &str):
    Matrix(str, 1, AlgorithmType::Slow) {}

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

    else if (lhs._type != rhs._type)
        throw AlgorithmTypeError();

    Matrix sum(lhs);

    for (size_t i = 0; i < sum.shape().first; ++i)
        sum._mat[i] = sum._mat[i] + rhs._mat[i];

    return sum;
}


const Matrix operator+ (const Matrix& matrix, const GString& str)
{
    if (matrix.shape().second != str.shape())
        throw DimensionsError();

    Matrix sum(matrix);

    for (size_t i = 0; i < sum.shape().first; ++i)
        sum._mat[i] = sum._mat[i] + str;

    return sum;
}

const Matrix operator+ (const GString& str, const Matrix& matrix)
{
    return matrix + str;
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
    if (lhs._n_jobs == 1 && lhs._type == AlgorithmType::Slow)
        return lhs.__dotSlow(rhs);

    return lhs * 0;
}


const Matrix operator* (const Matrix& lhs, const GString& rhs)
{
    Matrix rhs_mat(rhs, lhs._n_jobs, lhs._type);

    if (lhs._n_jobs == 1 && lhs._type == AlgorithmType::Slow)
        return lhs.__dotSlow(rhs_mat);

    return lhs * 0;
}


const GString operator* (const GString& lhs, const Matrix& rhs)
{
    Matrix lhs_mat(lhs, rhs._n_jobs, rhs._type);

    if (lhs_mat._n_jobs == 1 && lhs_mat._type == AlgorithmType::Slow)
        return lhs_mat.__dotSlow(rhs)[0];

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
    _type = matrix._type;

    return *this;
}

// Оператор доступа к элементам
const GString& Matrix::operator[](size_t i) const
{
    return _mat[i];
}


GString& Matrix::operator[](size_t i)
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
    Matrix transposed(shape().second, shape().first, _n_jobs, _type);

    for (size_t i = 0; i < shape().first; ++i)
        for (size_t j = 0; j < shape().second; ++j)
            transposed._mat[j][i] = _mat[i][j];

    return transposed;
}

//----------------------------------------------------------------------------------------------------------------------
// Блок приватных методов
//----------------------------------------------------------------------------------------------------------------------

const Matrix Matrix::__dotSlow(const Matrix &rhs) const
{
    if (shape().second != rhs.shape().first)
        throw DimensionsError();

    else if (_n_jobs != rhs._n_jobs)
        throw MultiprocessingError();

    else if (_type != rhs._type)
        throw AlgorithmTypeError();

    Matrix product(shape().first, rhs.shape().second, _n_jobs, _type);

    for (size_t i = 0; i < shape().first; ++i)
    {
        for (size_t j = 0; j < shape().second; ++j)
            product[i] = product[i] + _mat[i][j] * rhs[j];
    }

    return product;
}

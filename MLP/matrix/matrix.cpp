#include "Matrix.h"

//----------------------------------------------------------------------------------------------------------------------
// Блок конструкторов
//----------------------------------------------------------------------------------------------------------------------

Matrix::Matrix(size_t n, size_t m, double fill, size_t n_jobs, AlgorithmType type):
    n_jobs(n_jobs), type(type)
{
    mat = std::vector<std::vector<double>>(n, std::vector<double>(m, fill));
}


Matrix::Matrix(size_t n, size_t m, size_t n_jobs, AlgorithmType type):
    Matrix(n, m, 0, n_jobs, type) {}


Matrix::Matrix(std::vector<std::vector<double>> &table, size_t n_jobs, AlgorithmType type):
    mat(table), n_jobs(n_jobs), type(type) {}

//----------------------------------------------------------------------------------------------------------------------
// Блок перегруженных операторов
//----------------------------------------------------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.shape().first; ++i)
    {
        for (size_t j = 0; j < matrix.shape().second; ++j)
            os << matrix.mat[i][j] << " ";

        os << "\n";
    }

    return os;
}


const Matrix operator* (double num, const Matrix& matrix)
{
    Matrix multiplied(matrix);

    for (size_t i = 0; i < multiplied.shape().first; ++i)
        for (size_t j = 0; j < multiplied.shape().second; ++j)
            multiplied.mat[i][j] *= num;

    return multiplied;
}


const Matrix operator* (const Matrix& matrix, double num)
{
    return num * matrix;
}


const Matrix operator* (const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.n_jobs == 1 && lhs.type == AlgorithmType::Slow)
        return lhs.__dotSlow(rhs);

    return lhs * 0;
}


const Matrix operator+ (double num, const Matrix& matrix)
{
    Matrix added(matrix);

    for (size_t i = 0; i < added.shape().first; ++i)
        for (size_t j = 0; j < added.shape().second; ++j)
            added.mat[i][j] += num;

    return added;
}


const Matrix operator+ (const Matrix& matrix, double num)
{
    return num + matrix;
}


const Matrix operator- (double num, const Matrix& matrix)
{
    return -1 * matrix + num;
}


const Matrix operator- (const Matrix& matrix, double num)
{
    return matrix + (-num);
}

//----------------------------------------------------------------------------------------------------------------------
// Блок публичных методов
//----------------------------------------------------------------------------------------------------------------------

std::pair<size_t, size_t> Matrix::shape() const
/*
 * Возвращает пару {количество строк, количество столбцов}
 */
{
    if (mat.empty())
        return {0, 0};

    return {mat.size(), mat[0].size()};
}


Matrix Matrix::T() const
/*
 * Транспонирует матрицу
 *
 * Возвращает транспонированную матрицу
 */
{
    Matrix transposed(shape().second, shape().first, n_jobs, type);

    for (size_t i = 0; i < shape().first; ++i)
        for (size_t j = 0; j < shape().second; ++j)
            transposed.mat[j][i] = mat[i][j];

    return transposed;
}

//----------------------------------------------------------------------------------------------------------------------
// Блок приватных методов
//----------------------------------------------------------------------------------------------------------------------

const Matrix Matrix::__dotSlow(const Matrix &rhs) const
{

    bool shape_cond = shape().second != rhs.shape().first;          // размерности матриц не дают их перемножить
    bool dot_cond = shape().first == 1 && rhs.shape().second == 1;  // матрицы - не векторы
    bool jobs_cond = n_jobs != rhs.n_jobs;                          // разные уровни распараллеливания
    bool type_cond = type != rhs.type;                              // разные способы умножения

    // ничего не делаем, если матрицы несовместимы
    if ((shape_cond && !dot_cond) || jobs_cond || type_cond)
    // возможно, стоит переработать этот момент
    {
        std::cout << "Impossible to multiply matrices" << "\n";
        return rhs * 0;
    }

    Matrix product(shape().first, rhs.shape().second, n_jobs, type);

    for (size_t i = 0; i < product.shape().first; ++i)
        for (size_t j = 0; j < product.shape().second; ++j)
            for (size_t k = 0; k < shape().second; ++k)
                product.mat[i][j] += mat[i][k] * rhs.mat[k][j];

    return product;
}

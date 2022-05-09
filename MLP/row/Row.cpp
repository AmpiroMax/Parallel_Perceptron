#include <random>

#include "Row.h"
#include "../errors/errors.h"

//----------------------------------------------------------------------------------------------------------------------
// Блок конструкторов
//----------------------------------------------------------------------------------------------------------------------

Row::Row(size_t size, FillingType type, double fill)
{
    if (type == FillingType::UseFill)
        _row = std::vector<double>(size, fill);

    else
    {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<double> d;

        for (int i = 0; i < size; ++i)
            _row.emplace_back(d(gen));
    }
}

Row::Row(const std::vector<double>& v):
        _row(v) {}

Row::Row(const std::initializer_list<double>& list):
        _row(list.begin(), list.end()) {}

//----------------------------------------------------------------------------------------------------------------------
// Блок перегруженных операторов
//----------------------------------------------------------------------------------------------------------------------

// Ввод / вывод
std::ostream& operator<< (std::ostream& os, const Row& str)
{
    for (size_t i = 0; i < str._row.size(); ++i)
        os << str._row[i] << " ";

    return os;
}


std::istream& operator>> (std::istream& is, Row& str)
{
    for (size_t i = 0; i < str._row.size(); ++i)
        is >> str._row[i];

    return is;
}

// Оператор сложения
const Row operator+ (const Row& str, double num)
{
    Row sum(str);

    for (size_t i = 0; i < sum._row.size(); ++i)
        sum._row[i] += num;

    return sum;
}


const Row operator+ (double num, const Row& str)
{
    return str + num;
}


const Row operator+ (const Row& lhs, const Row& rhs)
{
    if (lhs.shape() != rhs.shape())
        throw DimensionsError();

    Row sum(lhs);

    for (size_t i = 0; i < sum.shape(); ++i)
        sum._row[i] += rhs._row[i];

    return sum;
}

// Оператор умножения
const Row operator* (const Row& str, double num)
{
    Row multiplied(str);

    for (size_t i = 0; i < multiplied.shape(); ++i)
        multiplied._row[i] *= num;

    return multiplied;
}


const Row operator* (double num, const Row& str)
{
    return str * num;
}

// Оператор вычитания
const Row operator- (const Row& str, double num)
{
    Row subtracted(str);

    for (size_t i = 0; i < subtracted.shape(); ++i)
        subtracted._row[i] -= num;

    return subtracted;
}


const Row operator- (double num, const Row& str)
{
    return (-1) * str + num;
}


const Row operator- (const Row& lhs, const Row& rhs)
{
    return lhs + ((-1) * rhs);
}

// Оператор деления
const Row operator/ (const Row& str, double num)
{
    Row divided(str);

    for (size_t i = 0; i < divided.shape(); ++i)
        divided._row[i] /= num;

    return divided;
}


const Row operator/ (double num, const Row& str)
{
    Row divided(str.shape(), FillingType::UseFill, num);

    for (size_t i = 0; i < divided.shape(); ++i)
        divided._row[i] /= str._row[i];

    return divided;
}

// Оператор присваивания
Row& Row::operator= (const Row &str)
{
    if (&str == this)
        return *this;

    _row = str._row;

    return *this;
}


// Оператор доступа к элементам
const double& Row::operator[](size_t i) const
{
    return _row[i];
}


double& Row::operator[](size_t i)
{
    return _row[i];
}

//----------------------------------------------------------------------------------------------------------------------
// Блок публичных методов
//----------------------------------------------------------------------------------------------------------------------

size_t Row::shape() const
{
    return _row.size();
}

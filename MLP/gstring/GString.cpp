#include "GString.h"
#include "../errors/errors.h"

//----------------------------------------------------------------------------------------------------------------------
// Блок конструкторов
//----------------------------------------------------------------------------------------------------------------------

GString::GString(size_t size, double fill):
    _gstring(size, fill) {}

GString::GString(size_t size):
    _gstring(size) {}

GString::GString(const std::vector<double>& v):
    _gstring(v) {}

GString::GString(const std::initializer_list<double>& list):
    _gstring(list.begin(), list.end()) {}

//----------------------------------------------------------------------------------------------------------------------
// Блок перегруженных операторов
//----------------------------------------------------------------------------------------------------------------------

// Ввод / вывод
std::ostream& operator<< (std::ostream& os, const GString& str)
{
    for (size_t i = 0; i < str._gstring.size(); ++i)
        os << str._gstring[i] << " ";

    return os;
}


std::istream& operator>> (std::istream& is, GString& str)
{
    for (size_t i = 0; i < str._gstring.size(); ++i)
        is >> str._gstring[i];

    return is;
}

// Оператор сложения
const GString operator+ (const GString& str, double num)
{
    GString sum(str);

    for (size_t i = 0; i < sum._gstring.size(); ++i)
        sum._gstring[i] += num;

    return sum;
}


const GString operator+ (double num, const GString& str)
{
    return str + num;
}


const GString operator+ (const GString& lhs, const GString& rhs)
{
    if (lhs.shape() != rhs.shape())
        throw DimensionsError();

    GString sum(lhs);

    for (size_t i = 0; i < sum.shape(); ++i)
        sum._gstring[i] += rhs._gstring[i];

    return sum;
}

// Оператор умножения
const GString operator* (const GString& str, double num)
{
    GString multiplied(str);

    for (size_t i = 0; i < multiplied.shape(); ++i)
        multiplied._gstring[i] *= num;

    return multiplied;
}


const GString operator* (double num, const GString& str)
{
    return str * num;
}

// Оператор вычитания
const GString operator- (const GString& str, double num)
{
    GString subtracted(str);

    for (size_t i = 0; i < subtracted.shape(); ++i)
        subtracted._gstring[i] -= num;

    return subtracted;
}


const GString operator- (double num, const GString& str)
{
    return (-1) * str + num;
}


const GString operator- (const GString& lhs, const GString& rhs)
{
    return lhs + ((-1) * rhs);
}

// Оператор деления
const GString operator/ (const GString& str, double num)
{
    GString divided(str);

    for (size_t i = 0; i < divided.shape(); ++i)
        divided._gstring[i] /= num;

    return divided;
}


const GString operator/ (double num, const GString& str)
{
    GString divided(str.shape(), num);

    for (size_t i = 0; i < divided.shape(); ++i)
        divided._gstring[i] /= str._gstring[i];

    return divided;
}

// Оператор присваивания
GString& GString::operator= (const GString &str)
{
    if (&str == this)
        return *this;

    _gstring = str._gstring;

    return *this;
}


// Оператор доступа к элементам
const double& GString::operator[](size_t i) const
{
    return _gstring[i];
}


double& GString::operator[](size_t i)
{
    return _gstring[i];
}

//----------------------------------------------------------------------------------------------------------------------
// Блок публичных методов
//----------------------------------------------------------------------------------------------------------------------

size_t GString::shape() const
{
    return _gstring.size();
}

#ifndef MLP_GSTRING_H
#define MLP_GSTRING_H

#include <initializer_list>
#include <iostream>
#include <vector>

using std::size_t;

/*
 *  Класс GString реализует строку, как объект линейной алгебры
 */


class GString
{
private:

    std::vector<double> _gstring;

public:

    GString() = default;
    explicit GString(size_t size);
    explicit GString(size_t size, double fill);
    explicit GString(const std::vector<double>& v);
    GString(const std::initializer_list<double>& list);

    friend std::ostream& operator<< (std::ostream& os, const GString& str);
    friend std::istream& operator>> (std::istream& is, GString& str);

    friend const GString operator+ (const GString& str, double num);
    friend const GString operator+ (double num, const GString& str);
    friend const GString operator+ (const GString& lhs, const GString& rhs);

    friend const GString operator* (const GString& str, double num);
    friend const GString operator* (double num, const GString& str);

    friend const GString operator- (const GString& str, double num);
    friend const GString operator- (double num, const GString& str);
    friend const GString operator- (const GString& lhs, const GString& rhs);

    friend const GString operator/ (const GString& str, double num);
    friend const GString operator/ (double num, const GString& str);

    GString& operator= (const GString& str);

    const double& operator[] (size_t i) const;
    double& operator[] (size_t i);

    size_t shape() const;
};


#endif //MLP_GSTRING_H

#ifndef MLP_ROW_H
#define MLP_ROW_H

#include <initializer_list>
#include <iostream>
#include <vector>

#include "../constants.h"

using std::size_t;

/*
 *  Класс Row реализует строку, как объект линейной алгебры
 */


class Row
{
private:

    std::vector<double> _row;

public:

    Row() = default;
    explicit Row(size_t size, FillingType type=FillingType::UseFill, double fill=0);
    explicit Row(const std::vector<double>& v);
    Row(const std::initializer_list<double>& list);

    friend std::ostream& operator<< (std::ostream& os, const Row& str);
    friend std::istream& operator>> (std::istream& is, Row& str);

    friend const Row operator+ (const Row& str, double num);
    friend const Row operator+ (double num, const Row& str);
    friend const Row operator+ (const Row& lhs, const Row& rhs);

    friend const Row operator* (const Row& str, double num);
    friend const Row operator* (double num, const Row& str);

    friend const Row operator- (const Row& str, double num);
    friend const Row operator- (double num, const Row& str);
    friend const Row operator- (const Row& lhs, const Row& rhs);

    friend const Row operator/ (const Row& str, double num);
    friend const Row operator/ (double num, const Row& str);

    Row& operator= (const Row& str);

    const double& operator[] (size_t i) const;
    double& operator[] (size_t i);

    size_t shape() const;
};


#endif //MLP_ROW_H

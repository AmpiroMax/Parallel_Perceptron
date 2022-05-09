#ifndef MLP_ERRORS_H
#define MLP_ERRORS_H

#include <exception>

/*
 *  Здесь находятся классы ошибок
 */

class DimensionsError : public std::exception
/*
 *  Ошибка размерностей
 *
 *  Появляется при несоответсвии размерностей операндов
 *  арифметических операций
 */
{
    const char* what() const noexcept override
    {
        return "DimensionsError: operands have different dimensions;\n";
    }
};


class MultiprocessingError : public std::exception
/*
 * Ошибка несоответсвия количества процессов
 *
 * Появляется при разнои уровне распараллеливания
 * алгоритмлв в матрицах
 */
{
    const char* what() const noexcept override
    {
        return "MultiprocessingError: operands have different parallel degrees;\n";
    }
};

#endif //MLP_ERRORS_H

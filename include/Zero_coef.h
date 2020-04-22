#ifndef ZERO_COEF_H
#define ZERO_COEF_H

#include <exception>


class Zero_coef : public std::exception
{
public:
    Zero_coef() noexcept {}
    Zero_coef(const Zero_coef&) noexcept = default;
    Zero_coef& operator=(const Zero_coef&) noexcept = default;
    virtual ~Zero_coef() noexcept = default;
    virtual const char* what() const noexcept{
        return "Coeficientul unui monom de grad pozitiv trebuie sa fie nenul!\n";
    }
};

#endif // ZERO_COEF_H

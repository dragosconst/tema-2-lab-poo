#ifndef SAME_POLY_H
#define SAME_POLY_H

#include <exception>


class Same_poly : public std::exception
{
public:
    Same_poly() noexcept {}
    Same_poly(const Same_poly&) noexcept = default;
    Same_poly& operator=(const Same_poly&) noexcept = default;
    virtual ~Same_poly() noexcept = default;
    virtual const char* what() const noexcept{
        return "Polinomul este de fapt ireductibil";
    }
};

#endif // SAME_POLY_H

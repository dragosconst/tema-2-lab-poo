#ifndef POLY_IS_NOT_IRED_H
#define POLY_IS_NOT_IRED_H

#include <exception>


class Poly_is_not_ired : public std::exception
{
public:
    Poly_is_not_ired() noexcept {}
    Poly_is_not_ired(const Poly_is_not_ired&) noexcept = default;
    Poly_is_not_ired& operator=(const Poly_is_not_ired&) noexcept = default;
    virtual ~Poly_is_not_ired() noexcept = default;
    virtual const char* what() const noexcept{
        return "Polinomul nu este ireductibil!Probabil incerci sa construiesti un obiect de Polinom_ireductibil...";
    }
};

#endif // POLY_IS_NOT_IRED_H

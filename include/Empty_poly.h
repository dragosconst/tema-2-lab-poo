#ifndef EMPTY_POLY_H
#define EMPTY_POLY_H

#include <exception>


class Empty_poly : public std::exception
{
public:
    Empty_poly() noexcept {}
    Empty_poly(const Empty_poly&) noexcept = default;
    Empty_poly& operator=(const Empty_poly&) noexcept = default;
    virtual ~Empty_poly() noexcept = default;
    virtual const char* what() const noexcept{
        return "Polinomul e gol! Poate incerci sa faci o operatie cu el...\n";
    }
};

#endif // EMPTY_POLY_H

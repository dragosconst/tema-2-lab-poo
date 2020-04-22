#ifndef DIVISION_BY_ZERO_H
#define DIVISION_BY_ZERO_H

#include <exception>


class Division_by_zero : public std::exception
{
public:
    Division_by_zero() noexcept {}
    Division_by_zero(const Division_by_zero&) noexcept = default;
    Division_by_zero& operator=(const Division_by_zero&) noexcept = default;
    virtual ~Division_by_zero() noexcept = default;
    virtual const char* what() const noexcept{
        return "Nu se poate imparti cu un monom nul!\n";
    }
};

#endif // DIVISION_BY_ZERO_H

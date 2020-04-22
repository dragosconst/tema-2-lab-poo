#ifndef DEGREE_TO_SMALL_H
#define DEGREE_TO_SMALL_H

#include <exception>


class Degree_too_small : public std::exception
{
public:
    Degree_too_small() noexcept {}
    Degree_too_small(const Degree_too_small&) noexcept = default;
    Degree_too_small& operator=(const Degree_too_small&) noexcept = default;
    virtual ~Degree_too_small() noexcept = default;
    virtual const char* what() const noexcept{
        return "Nu se poate imparti un monom la alt monom cu un grad mai mare!\n";
    }
};

#endif // DEGREE_TO_SMALL_H

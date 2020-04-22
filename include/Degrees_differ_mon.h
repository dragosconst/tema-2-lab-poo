#ifndef DEGREES_DIFFER_MON_H
#define DEGREES_DIFFER_MON_H

#include <exception>


class Degrees_differ_mon : public std::exception
{
public:
    Degrees_differ_mon() noexcept {}
    Degrees_differ_mon(const Degrees_differ_mon&) noexcept = default;
    Degrees_differ_mon& operator=(const Degrees_differ_mon&) noexcept = default;
    virtual ~Degrees_differ_mon() noexcept = default;
    virtual const char* what() const noexcept{
        return "Grade diferite la operatii cu monoame!\n";
    }

};

#endif // DEGREES_DIFFER_MON_H

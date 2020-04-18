#ifndef DIVISION_BY_ZERO_H
#define DIVISION_BY_ZERO_H

#include <exception>


class Division_by_zero : public std::exception
{
    public:
        Division_by_zero();
        virtual ~Division_by_zero();

    protected:

    private:
};

#endif // DIVISION_BY_ZERO_H

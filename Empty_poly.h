#ifndef EMPTY_POLY_H
#define EMPTY_POLY_H

#include <exception>


class Empty_poly : public std::exception
{
    public:
        Empty_poly();
        virtual ~Empty_poly();

    protected:

    private:
};

#endif // EMPTY_POLY_H

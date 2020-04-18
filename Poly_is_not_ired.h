#ifndef POLY_IS_NOT_IRED_H
#define POLY_IS_NOT_IRED_H

#include <exception>


class Poly_is_not_ired : public std::exception
{
    public:
        Poly_is_not_ired();
        virtual ~Poly_is_not_ired();

    protected:

    private:
};

#endif // POLY_IS_NOT_IRED_H

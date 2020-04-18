#ifndef ZERO_COEF_H
#define ZERO_COEF_H

#include <exception>


class Zero_coef : public std::exception
{
    public:
        Zero_coef();
        virtual ~Zero_coef();

    protected:

    private:
};

#endif // ZERO_COEF_H

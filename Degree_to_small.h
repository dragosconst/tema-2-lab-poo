#ifndef DEGREE_TO_SMALL_H
#define DEGREE_TO_SMALL_H

#include <exception>


class Degree_too_small : public std::exception
{
    public:
        Degree_too_small();
        virtual ~Degree_too_small();

    protected:

    private:
};

#endif // DEGREE_TO_SMALL_H

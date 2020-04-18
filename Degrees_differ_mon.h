#ifndef DEGREES_DIFFER_MON_H
#define DEGREES_DIFFER_MON_H

#include <exception>


class Degrees_differ_mon : public std::exception
{
public:
    Degrees_differ_mon();
    virtual ~Degrees_differ_mon();

};

#endif // DEGREES_DIFFER_MON_H

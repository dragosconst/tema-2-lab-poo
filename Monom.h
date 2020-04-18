#ifndef MONOM_H
#define MONOM_H
#define INF (1<<30)

#include <istream>
#include <ostream>
#include <Degrees_differ_mon.h>
#include <Division_by_zero.h>
#include <Degree_to_small.h>
#include <Zero_coef.h>
#include <iostream>

class Monom
{
    int grad;
    float coef;
public:
    Monom();
    Monom(int, float);
    virtual ~Monom();
    Monom(const Monom& other);
    Monom& operator=(const Monom& other);

    int getGrad() const { return grad; }
    void setGrad(int val) { grad = val; }
    float getCoef() const { return coef; }
    void setCoef(float val) { coef = val; }

    Monom operator+(const Monom&) const;
    Monom operator-(const Monom&) const;
    Monom operator*(const Monom&) const;
    friend Monom operator*(const Monom&, float);
    friend Monom operator*(float, const Monom&);
    Monom operator/(const Monom&) const;

    friend std::istream& operator>>(std::istream&, Monom&);
    friend std::ostream& operator<<(std::ostream&, const Monom&);

    static bool cmp(Monom, Monom);
    bool null() const { return this->coef == 0; }
};

#endif // MONOM_H

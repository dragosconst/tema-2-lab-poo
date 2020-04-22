#include "Monom.h"

Monom::Monom()
{
    this->grad = -INF; // INF e un macro definit cu 2^30
    this->coef = 0;
}
Monom::Monom(int grad, float coef)
{
    if(coef == 0 && grad != -INF) throw Zero_coef();
    this->grad = grad;
    this->coef = coef;
}

Monom::~Monom()
{
}

Monom::Monom(const Monom& other)
{
    this->grad = other.grad;
    this->coef = other.coef;
}

Monom& Monom::operator=(const Monom& other)
{
    if (this == &other) return *this; // handle self assignment
    this->grad = other.grad;
    this->coef = other.coef;
    return *this;
}

Monom Monom::operator+(const Monom& other) const
{
    Monom rez;
    if(this->grad != other.grad
        && (this->grad != -INF && other.grad != -INF)) throw Degrees_differ_mon(); // monoame de grade diferite nu pot fi adunate intre ele, cu exceptia gradului -INFINIT
    rez.coef = this->coef + other.coef;
    rez.grad = this->grad;
    if(rez.coef == 0) rez.grad = -INF;
    return rez;
}
Monom Monom::operator-(const Monom& other) const
{
    Monom rez;
    if(this->grad != other.grad
        && (this->grad != -INF && other.grad != -INF)) throw Degrees_differ_mon(); // monoame de grade diferite nu pot fi adunate intre ele, cu exceptia gradului -INFINIT
    rez.coef = this->coef - other.coef;
    rez.grad = this->grad;
    if(rez.coef == 0) rez.grad = -INF;
    return rez;
}
Monom Monom::operator*(const Monom& other) const
{
    Monom rez;
    if(this->grad == -INF || other.grad == -INF)
    {
        return Monom(); // inmultirea cu un monom nul rezulta alt monom nul
    }
    rez.grad = this->grad + other.grad;
    rez.coef = this->coef * other.coef;
    return rez;
}
Monom operator*(const Monom& m, float x) // inmultire cu un scalar
{
    Monom rez;
    if(m.grad == -INF || x == 0)
    {
        return rez; // monom nul
    }
    rez.coef = m.coef * x;
    rez.grad = m.grad;
    return rez;
}
Monom operator*(float x, const Monom& m)
{
    return operator*(m, x);
}
Monom Monom::operator/(const Monom& other) const
{
    Monom rez;
    if(other.grad == -INF) throw Division_by_zero();
    if(this->grad == -INF)
    {
        return Monom(); // daca monomul deimpartit e zero rezultatul e tot zero
    }
    if(this->grad < other.grad) throw Degree_too_small();
    rez.grad = this->grad - other.grad;
    rez.coef = this->coef / other.coef;
    return rez;

}

std::istream& operator>>(std::istream& in, Monom& m)
{
    int grad, coef;
    in >> grad >> coef;
    m.grad = grad;
    m.coef = coef;
    if(coef == 0 && grad >= 0) throw Zero_coef();
    if(coef == 0 || grad < 0) m.grad = -INF; // am pus optiunea ca orice grad negativ la citire sa fie tratat ca polinomul nul pt a simplifica intrarile
    return in;
}
std::ostream& operator<<(std::ostream& out, const Monom& m)
{
    if(m.coef)
        if(m.coef != 1)
            out << m.coef << "x^" << m.grad;
        else out << "x^" << m.grad;
    else out << "0";
    return out;
}

bool Monom::cmp(Monom m1, Monom m2) // pentru sortari
{
    return m1.grad <= m2.grad;
}

#include "Polinom_ireductibil.h"

Polinom_ireductibil::Polinom_ireductibil() : Polinom()
{

}
Polinom_ireductibil::Polinom_ireductibil(int grad, Monom* m) : Polinom(grad, m)
{
    try{
        if(!this->reducedForm().empty()) throw Poly_is_not_ired();
    }
    catch(Poly_is_not_ired& pisni)
    {
        std::cout << "Polinomul nu este ireductibil!";
        exit(EXIT_FAILURE);
    }
}

Polinom_ireductibil::~Polinom_ireductibil()
{
    //dtor
}

Polinom_ireductibil::Polinom_ireductibil(const Polinom& other)
{
    try{
        if(!other.reducedForm().empty()) throw Poly_is_not_ired();
        this->grad = other.getGrad();
        this->nr_monoame = other.getNrMonoame();
        this->monoame = new Monom[nr_monoame];
        for(int i = 0; i < this->nr_monoame; ++i)
        {
            this->monoame[i] = other.getMonoame()[i];
        }
    }
    catch(Poly_is_not_ired& pisni)
    {
        std::cout << "Polinomul ce trebuie copiat nu e ireductibil!";
        exit(EXIT_FAILURE);
    }
}
Polinom_ireductibil& Polinom_ireductibil::operator=(const Polinom& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    try{
        if(!rhs.reducedForm().empty()) throw Poly_is_not_ired();
        this->grad = rhs.getGrad();
        this->nr_monoame = rhs.getNrMonoame();
        this->monoame = new Monom[nr_monoame]; // am decis sa fac un deep copy si la egalitate
        for(int i = 0; i < this->nr_monoame; ++i)
        {
            this->monoame[i] = rhs.getMonoame()[i];
        }
        return *this;
    }
    catch(Poly_is_not_ired& pisni)
    {
        std::cout << "Polinomul din dreapta egalului nu e ireductibil!";
        exit(EXIT_FAILURE);
    }
}

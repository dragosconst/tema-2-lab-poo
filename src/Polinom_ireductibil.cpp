#include "Polinom_ireductibil.h"

Polinom_ireductibil::Polinom_ireductibil() : Polinom()
{

}
Polinom_ireductibil::Polinom_ireductibil(int grad, Monom* m) : Polinom(grad, m)
{
    if(this->isReductible()) throw Poly_is_not_ired();
}

Polinom_ireductibil::~Polinom_ireductibil()
{
    //dtor
}

Polinom_ireductibil::Polinom_ireductibil(const Polinom& other)
{
    if(other.isReductible()) throw Poly_is_not_ired();
    this->grad = other.getGrad();
    this->nr_monoame = other.getNrMonoame();
    this->monoame = new Monom[nr_monoame];
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        this->monoame[i] = other.getMonoame()[i];
    }
    this->avoidLeaks = other.getLeaks();
    this->coefs = new int[this->grad <= -INF ? 1 : this->grad + 1];
    int i_m = 0, i_c = 0;
    while(i_m < nr_monoame)
    {
        if(this->monoame[i_m].getGrad() == i_c
            ||(!this->monoame[i_m].getCoef() && i_c == 0))
            this->coefs[i_c++] = this->monoame[i_m++].getCoef();
        else
            this->coefs[i_c++] = 0;
    }
}
Polinom_ireductibil& Polinom_ireductibil::operator=(const Polinom& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    if(rhs.isReductible()) throw Poly_is_not_ired();
    this->grad = rhs.getGrad();
    this->nr_monoame = rhs.getNrMonoame();
    if(this->monoame != nullptr)
        delete[] this->monoame;
    if(this->coefs != nullptr)
        delete[] this->coefs;
        this->monoame = new Monom[nr_monoame]; // am decis sa fac un deep copy si la egalitate
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        this->monoame[i] = rhs.getMonoame()[i];
    }
    // ca sa ma asigur ca functia reducedForm nu da memory leaks
    for(std::vector<Polinom*>::iterator it = this->avoidLeaks.begin(); it != this->avoidLeaks.end(); ++it)
    {
        delete *it;
    }
    this->avoidLeaks = rhs.getLeaks();
    this->coefs = new int[this->grad <= -INF ? 1 : this->grad + 1];
    int i_m = 0, i_c = 0;
    while(i_m < nr_monoame)
    {
        if(this->monoame[i_m].getGrad() == i_c
            ||(!this->monoame[i_m].getCoef() && i_c == 0))
            this->coefs[i_c++] = this->monoame[i_m++].getCoef();
        else
            this->coefs[i_c++] = 0;
    }
    return *this;
}

std::vector<Polinom*> Polinom_ireductibil::reducedForm()
{
    Polinom* temp = new Polinom(*this);
    std::vector<Polinom*> ret;
    ret.push_back(temp);
    return ret;
}

std::istream& operator>>(std::istream& in, Polinom_ireductibil& poli)
{
    in >> poli.nr_monoame;
    poli.monoame = new Monom[poli.nr_monoame];
    poli.grad = -INF - 1;
    for(int i = 0; i < poli.nr_monoame; ++i)
    {
        in >> poli.monoame[i];
        if(poli.monoame[i].getGrad() > poli.grad)
            poli.grad = poli.monoame[i].getGrad();
    }
    std::sort(poli.monoame, poli.monoame + poli.nr_monoame, Monom::cmp); // in cazul in care lista de monoame nu e data gata sortata dupa grade
    if(poli.isReductible()) throw Poly_is_not_ired();
    return in;
}

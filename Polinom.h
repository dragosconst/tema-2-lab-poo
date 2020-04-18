#ifndef POLINOM_H
#define POLINOM_H

#include <Monom.h>
#include <Empty_poly.h>
#include <Division_by_zero.h>
#include <algorithm>
#include <vector>
#include <set>

//functia de descompunere o fac virtuala pura
class Polinom
{
protected:
    int nr_monoame;
    Monom* monoame;
    int grad;
public:
    Polinom();
    Polinom(int, Monom*);
    virtual ~Polinom();
    Polinom(const Polinom& other);
    Polinom& operator=(const Polinom& other);

    int getNrMonoame() const { return nr_monoame; }
    Monom* getMonoame() const { return monoame; }
    int getGrad() const { return grad; }
    float getLeadingCoef() const;

    Polinom operator+(const Polinom&) const;
    Polinom& operator+=(const Polinom&);
    Polinom operator-(const Polinom&) const;
    Polinom& operator-=(const Polinom&);
    Polinom operator*(const Polinom&) const;
    friend Polinom operator*(const Polinom&, const Monom&);
    friend Polinom operator*(const Monom&, const Polinom&);
    Polinom& operator*=(const Polinom&);
    friend std::pair<Polinom, Polinom> operator/(const Polinom&, const Polinom&);

    friend std::istream& operator>>(std::istream&, Polinom&);
    friend std::ostream& operator<<(std::ostream&, const Polinom&);

    virtual bool iredEinstein();
    virtual std::vector<Polinom*> reducedForm() const;
    virtual void showReducedForm();

    float plugInNumber(float) const;
    void addMonom(Monom);
    void removeMonom(int);
    bool emptyPoly() const { return nr_monoame == 0; }

};

void buildFactors(int, std::set<int>&); // functia asta face codul mai lizibil in unele cazuri; in vectorul de int-uri o sa puna toti factorii primi ai int-ului dat ca argument

#endif // POLINOM_H

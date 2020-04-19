#ifndef POLINOM_IREDUCTIBIL_H
#define POLINOM_IREDUCTIBIL_H

#include <Polinom.h>
#include <Poly_is_not_ired.h>

class Polinom_ireductibil : public Polinom
{
public:
    Polinom_ireductibil();
    Polinom_ireductibil(int, Monom*);
    Polinom_ireductibil(const Polinom&);
    ~Polinom_ireductibil();
    Polinom_ireductibil& operator=(const Polinom&);

    bool iredEinstein() { return true; }
    std::vector<Polinom*> reducedForm();
    void showReducedForm() { std::cout << *this; }

    friend std::istream& operator>>(std::istream&, Polinom_ireductibil&);
};

#endif // POLINOM_IREDUCTIBIL_H

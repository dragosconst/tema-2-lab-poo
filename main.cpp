#include <iostream>
#include <fstream>
#include <Polinom_ireductibil.h>
using namespace std;

void coolLongDivision(Polinom*, Polinom*);

int main()
{
    ifstream in("date.in");
    Polinom* p, *q;
    Polinom* temp = new Polinom;
    try{
        in >> *temp;
        if(temp->isReductible())
            p = new Polinom(*temp);
        else p = new Polinom_ireductibil(*temp);
        delete temp;
        temp = new Polinom;
        in >> *temp;
        if(temp->isReductible())
        {
            q = new Polinom(*temp);
        }
        else q = new Polinom_ireductibil(*temp);
        delete temp;

        cout << "P este " << *p << "\nQ este " << *q
        << "\nP + Q = " << *p + *q << "\nP in forma redusa e ";p->showReducedForm();
        cout << "\nQ in forma redusa este ";q->showReducedForm();
    }
    catch(std::exception& e)
    {
        cout << e.what();
        exit(EXIT_FAILURE);
    }
    return 0;
}


#include <iostream>
#include <fstream>
#include <Polinom_ireductibil.h>
using namespace std;

void coolLongDivision(Polinom*, Polinom*);

int main()
{
    ifstream in("date.in");
    Polinom_ireductibil pi;
    Polinom p,q;
    in >> p >> q;
    cout << '\n';
    coolLongDivision(&p, &q);
    return 0;
}

// o functie care face impartirea la doua polinoame si care ilustreaza polimorfismul claselor
void coolLongDivision(Polinom* f, Polinom* g)
{
    bool finishedDiv = false;
    cout << *f << '\n';
    for(int i = 0; i < 50; ++i) // ca un fel de linie de fractie
    {
        cout << "-";
    }
    cout << "\n";
    cout << *g << '\n';
    cout << "\n\t||\n\t\||\n\t\\/\n";
    while(!finishedDiv)
    {
        finishedDiv = true;
        f->showReducedForm();
        cout << "\n";
        for(int i = 0; i < 50; ++i) // ca un fel de linie de fractie
        {
            cout << "-";
        }
        cout << "\n";
        g->showReducedForm();
        if(f->getGrad() == 0 && f->getLeadingCoef() == 1) break; // adica cand e 1 la numitor, daca nu dau break e posibil sa intre intr o bucla infinita cand e 1 jos

        vector<Polinom*> f_factors = f->reducedForm(), g_factors = g->reducedForm();
        for(vector<Polinom*>::iterator it_f = f_factors.begin(); it_f != f_factors.end(); ++it_f)
        {
            for(vector<Polinom*>::iterator it_g = g_factors.begin(); it_g != g_factors.end(); ++it_g)
            {
                if(**it_f == **it_g) // daca gasesc un polinom comun in scrierea ambelor, il elimin
                {
                    *f = (Polinom(f->getNrMonoame(), f->getMonoame()) / **it_f).first;
                    *g = (Polinom(g->getNrMonoame(), g->getMonoame()) / **it_g).first;
                        finishedDiv = false;

                    it_f = f_factors.end() - 1; it_g = g_factors.end() - 1;
                }
            }
        }

        if(!finishedDiv)
        {
            cout << "\n\t||\n\t\||\n\t\\/\n";
        }
    }
}

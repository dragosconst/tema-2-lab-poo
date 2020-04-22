#include "Polinom.h"

Polinom::Polinom() // un polinom cu constructor gol va fi un polinom gol, distinct de un polinom nul
{
    this->nr_monoame = 0;
    this->monoame = nullptr;
    this->coefs = nullptr;
    this->grad = -INF - 1;
}
Polinom::Polinom(int nr_monoame, Monom* monoame)
{
    this->nr_monoame = nr_monoame;
    this->grad = -INF - 1;
    this->monoame = new Monom[nr_monoame];
    for(int i = 0; i < nr_monoame; ++i)
    {
        this->monoame[i] = monoame[i];
        if(this->monoame[i].getGrad() > this->grad)
            this->grad = this->monoame[i].getGrad();
    }
    std::sort(monoame, monoame + nr_monoame, Monom::cmp); // in cazul in care lista de monoame nu e data gata sortata dupa grade
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

Polinom::~Polinom()
{
    if(this->monoame)
        delete[] this->monoame;
    if(this->coefs)
        delete[] this->coefs;
    this->monoame = nullptr;
    // ca sa ma asigur ca functia reducedForm nu da memory leaks
    for(std::vector<Polinom*>::iterator it = this->avoidLeaks.begin(); it != this->avoidLeaks.end(); ++it)
    {
        delete *it;
    }
}

Polinom::Polinom(const Polinom& other)
{
    this->grad = other.grad;
    this->nr_monoame = other.nr_monoame;
    this->monoame = new Monom[nr_monoame];
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        this->monoame[i] = other.monoame[i];
    }
    this->avoidLeaks = other.avoidLeaks;
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

Polinom& Polinom::operator=(const Polinom& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->grad = rhs.grad;
    this->nr_monoame = rhs.nr_monoame;
    if(this->monoame != nullptr)
    {
        delete[] this->monoame;
    }
    if(this->coefs != nullptr)
    {
        delete[] this->coefs;
    }
    this->monoame = new Monom[nr_monoame]; // am decis sa fac un deep copy si la egalitate
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        this->monoame[i] = rhs.monoame[i];
    }
    // ca sa ma asigur ca functia reducedForm nu da memory leaks
    std::vector<Polinom*>::iterator it = this->avoidLeaks.begin();
    for(std::vector<Polinom*>::iterator it = this->avoidLeaks.begin(); it != this->avoidLeaks.end(); ++it)
    {
        delete *it;
    }
    this->avoidLeaks = rhs.avoidLeaks;
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
Polinom Polinom::operator+(const Polinom& other) const
{
    if(this->emptyPoly() || other.emptyPoly()) throw Empty_poly();
    Polinom rez;
    int ind_left = 0, ind_right = 0;
    while(ind_left < this->nr_monoame && ind_right < other.nr_monoame) // algoritmul face un fel de interclasare a polinoamelor pt suma
    {
        Monom temp;
        if(this->monoame[ind_left].getGrad() == other.monoame[ind_right].getGrad())
        {
            temp = this->monoame[ind_left++] + other.monoame[ind_right++];
        }
        else if(this->monoame[ind_left].getGrad() < other.monoame[ind_right].getGrad())
        {
            temp = this->monoame[ind_left++];
        }
        else
        {
            temp = other.monoame[ind_right++];
        }

        if(!temp.null())
            rez.addMonom(temp);
        else if(rez.emptyPoly() || rez.getMonoame()[0].getGrad() > 0) //  conditii ca sa nu fie adaugate monoame nule de mai multe ori
                rez.addMonom(Monom());
    }
    while(ind_left < this->nr_monoame)
    {
        rez.addMonom(this->monoame[ind_left++]);
    }
    while(ind_right < other.nr_monoame)
    {
        rez.addMonom(other.monoame[ind_right++]);
    }
    return rez;
}
Polinom& Polinom::operator+=(const Polinom& other)
{
    Polinom temp = *this + other;
    delete[] monoame;
    this->monoame = nullptr;
    *this = temp;
    return *this;
}
Polinom Polinom::operator-(const Polinom& other) const
{
    if(this->emptyPoly() || other.emptyPoly()) throw Empty_poly();
    Polinom rez;
    int ind_left = 0, ind_right = 0;
    while(ind_left < this->nr_monoame && ind_right < other.nr_monoame) // algoritmul face un fel de interclasare a polinoamelor pt suma
    {
        Monom temp;
        if(this->monoame[ind_left].getGrad() == other.monoame[ind_right].getGrad())
        {
            temp = this->monoame[ind_left++] - other.monoame[ind_right++];
        }
        else if(this->monoame[ind_left].getGrad() < other.monoame[ind_right].getGrad())
        {
            temp = this->monoame[ind_left++];
        }
        else
        {
            temp = other.monoame[ind_right++] * -1;
        }

        if(!temp.null()) // nu are rost sa fie adaugate monoame nule
           rez.addMonom(temp);
        else if(rez.emptyPoly() || rez.getMonoame()[0].getGrad() > 0) //  conditii ca sa nu fie adaugate monoame nule de mai multe ori
            rez.addMonom(Monom());
    }
    while(ind_left < this->nr_monoame)
    {
        rez.addMonom(this->monoame[ind_left++]);
    }
    while(ind_right < other.nr_monoame)
    {
        rez.addMonom(other.monoame[ind_right++] * -1);
    }
    return rez;
}
Polinom Polinom::operator*(const Polinom& other) const
{
    if(this->emptyPoly() || other.emptyPoly()) throw Empty_poly();
    Polinom rez;
    int tempArrSize = std::min(this->nr_monoame, other.nr_monoame); // o sa fac un vector temporar cu toate rezultatele partiale de la impartire, iar apoi le adun
    if(!tempArrSize) // daca un polinom e gol nu se poate face nicio impartire
        return rez;
    Polinom* polinoame = new Polinom[tempArrSize]; // ex: (x+1)(x+2) -> da vectoru x^2+2x, x + 2 => rezultatul final e obtinut prin adunarea rezultatelor
    for(int i = 0; i < tempArrSize; ++i)
    {
        if(this->nr_monoame < other.nr_monoame)
        {
            Monom tempFactor = this->monoame[i];
            for(int j = 0; j < other.nr_monoame; ++j)
            {
                polinoame[i].addMonom(tempFactor * other.getMonoame()[j]);
            }
        }
        else
        {
            Monom tempFactor = other.monoame[i];
            for(int j = 0; j < this->nr_monoame; ++j)
            {
                polinoame[i].addMonom(tempFactor * this->getMonoame()[j]);
            }
        }
    }
    rez = polinoame[0];
    for(int i = 1; i < tempArrSize; ++i) // adun toate polinoamele rezultate
    {
        rez += polinoame[i];
    }
    delete[] polinoame; // dezaloc memoria folosita in functie

    return rez;
}
Polinom operator*(const Polinom& p, const Monom& m)
{
    Polinom rez, temp;
    temp.addMonom(m);
    rez = p * temp;
    return rez;
}
Polinom operator*(const Monom& m, const Polinom& p)
{
    return operator*(p, m);
}
std::pair<Polinom, Polinom> operator/(const Polinom& p1, const Polinom& p2) // folosesc un pair pt ca vreau sa returnez si catul, si restul
{
    if(p1.emptyPoly() || p2.emptyPoly()) throw Empty_poly();
    Polinom q, r;
    if(p1.getGrad() < p2.getGrad()) // daca p2 are grad mai mare, catul e automat 0 si restul egal cu p1
    {
        q.addMonom(Monom());
        r = p1;
        return {q, r};
    }
    if(p2.getGrad() == -INF) throw Division_by_zero();
    Polinom temp = p1;
    while(temp.getGrad() >= p2.getGrad())
    {
        Polinom reminder;
        Monom mon_rem(temp.getGrad() - p2.getGrad(), temp.getLeadingCoef() / p2.getLeadingCoef()); // e algoritmu normal de impartire la polinoame
        reminder = mon_rem * p2; // iau fiecare grad si gasesc monomu cu care trebuie inmultit p2 ca sa ajung la gradul curent al lui p1;
        temp = temp - reminder;
        q.addMonom(mon_rem);
    }
    // acum catul e gata, restul e determinat printr-un simplu calcul
    r = p1 - p2 * q;
    return {q, r};
}

bool operator==(const Polinom& p1, const Polinom& p2)
{
    if(p1.grad != p2.grad)
        return false;
    if(p1.nr_monoame != p2.nr_monoame)
        return false;
    for(int i = 0; i < p1.nr_monoame; ++i)
        if(p1.monoame[i].getGrad() != p2.monoame[i].getGrad() || p1.monoame[i].getCoef() != p2.monoame[i].getCoef())
            return false;
    return true;
}
bool operator!=(const Polinom& p1, const Polinom& p2)
{
    return !operator==(p1, p2);
}
std::istream& operator>>(std::istream& in, Polinom& poli)
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
    return in;
}
std::ostream& operator<<(std::ostream& out, const Polinom& poli)
{
    for(int i = poli.nr_monoame - 1; i >= 0; --i)
    {
        out << poli.monoame[i];
        if(i != 0)
            out << " + ";
    }
    return out;
}

float Polinom::getLeadingCoef() const
{
    if(this->nr_monoame == 0) throw Empty_poly();
    return monoame[this->nr_monoame - 1].getCoef();
}

void Polinom::addMonom(Monom m) // metoda care adauga un nou monom in polinom
{
    Monom* temp = new Monom[this->nr_monoame + 1];
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        temp[i] = this->monoame[i];
    }
    temp[this->nr_monoame] = m;

    if(m.getGrad() > this->grad)
        this->grad = m.getGrad();
    this->nr_monoame++;
    delete[] this->monoame;
    this->monoame = new Monom[this->nr_monoame];
    for(int i = 0; i < this->nr_monoame; ++i)
        this->monoame[i] = temp[i];
    std::sort(this->monoame, this->monoame + this->nr_monoame, Monom::cmp);

    delete[] temp;
}

bool Polinom::iredEinstein() // Atentie!! Din moment ce nu e o conditie necesara(doar suficienta), e posibil sa existe polinoame ireductibile(sau reductibile) care sa nu fie gasite de metoda.
{
    if(this->emptyPoly()) throw Empty_poly();
    Monom firstTerm;
    int smallestCoef = INF; // iau si cel mai mic coeficient(fara ultimul) ca sa simplific cautarea de prime
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        if(this->monoame[i].getGrad() == 0)
        {
            firstTerm = this->monoame[i];
        }
        if(i != this->nr_monoame - 1 && this->monoame[i].getCoef() && abs(this->monoame[i].getCoef()) < smallestCoef)
        {
            smallestCoef = this->monoame[i].getCoef(); // folosesc abs pt ca semnul e irelevant pentru divizibilitate
        }
    }
    if(firstTerm.getGrad() != 0) // asta e totuna cu a0 = 0, caz in care polinomul nu poate fi ireductibil
        return false;
    for(int p = 2; p <= smallestCoef; ++p) // acum caut numaru prim cu pricina(daca exista)
    {
        bool ePrim = true;
        for(int ip = 2; ip * ip <= p; ++ip) // verific daca p e un nr prim
            if(p % ip == 0)
                {
                    ePrim = false;
                    break;
                }
        if(ePrim && (int)firstTerm.getCoef() % (p * p) != 0) // verific direct aici conditia ca p^2 sa nu divida a0
        {
            bool eOk = true;
            for(int i = 0; i < this->nr_monoame - 1; ++i)
            {
                if(this->monoame[i].getCoef() && (int)this->monoame[i].getCoef() % p != 0)
                {
                    eOk = false;
                    break;
                }
            }
            if(eOk)
            {
                if((int)this->getLeadingCoef() % p != 0)
                    return true;
            }
        }
    }
    return false; // daca a ajuns aici inseamna ca toate nr prime posibile au fost incercate si nu au mers
}

void buildFactors(int nr, std::set<int>& factors)
{
    for(int i = 2; i * i <= nr; ++i)
    {
        if(nr % i == 0)
        {
            factors.insert(i);
            factors.insert(-i);
            factors.insert(nr / i);
            factors.insert(-(nr / i));
        }
    }
    if(factors.empty()) // adica daca nr ul e prim
        factors.insert(nr), factors.insert(-nr), factors.insert(1), factors.insert(-1);
}

float Polinom::plugInNumber(float var) const // metoda asta returneaza rezultatul polinomului, in care valoarea din var e atribuita nedeterminatei x
{
    float rez = 0;
    for(int i = 0; i < this->nr_monoame; ++i)
    {
        float var_p = 1;
        for(int j = 1; j <= this->monoame[i].getGrad(); ++j) // ridic la puterea gradului
            var_p *= var;
        rez += this->monoame[i].getCoef() * var_p;
    }
    return rez;
}

bool Polinom::isReductible() const
{
    if(this->grad == 1) return false;
    std::set<int> constFactors, leadingFactors;
    int constTerm = 0, leadingTerm = this->getLeadingCoef();
    for(int i = 0; i < this->nr_monoame; ++i) // caut coeficientul termenului constant, daca nu apare in array u de monoame inseamna ca e zero
        if(this->monoame[i].getGrad() == 0)
        {
            constTerm = this->monoame[i].getCoef();
        }
        else if(this->monoame[i].getGrad() > 0)
            break;
    buildFactors(constTerm, constFactors);
    buildFactors(leadingTerm, leadingFactors);

    std::set<int>::iterator it = constFactors.begin();
    bool foundValue = false;
    float correctVal;
    for(; it != constFactors.end() && !foundValue; it++)
    {
        std::set<int>::iterator it_l = leadingFactors.begin();
        for(; it_l != leadingFactors.end() && !foundValue; ++it_l)
        {
            if(this->plugInNumber((float)(*it)/(float)(*it_l)) == 0)
            {
                foundValue = true;
                correctVal = (float)(*it)/(float)(*it_l);
                break;
            }
        }

    }
    if(foundValue == false)
    {
        return false;
    }
    // daca am ajuns aici, avem o radacina in correctVal
    // tot ce ramane de facut e de construit un polinom de grad 1 de forma x - correctVal si sa impart polinomu original la el
    Polinom first_factor;
    first_factor.addMonom(Monom(correctVal == 0 ? -INF : 0 , -correctVal));
    first_factor.addMonom(Monom(1, 1));
    if(first_factor == *this) return false;
    return true;

}

/// mai multe detalii despre algoritmul utilizat aici: https://en.wikipedia.org/wiki/Rational_root_theorem
std::vector<Polinom*> Polinom::reducedForm() // voi folosi radacini rationale pentru a determina o forma redusa a polinomului; daca nu are o sa-l consider ireductibil
{
    if(this->grad == 1)
    {
        std::vector<Polinom*> ret;
        Polinom* temp = new Polinom(*this);
        ret.push_back(temp);
        return ret;
    }
    std::set<int> constFactors, leadingFactors;
    int constTerm = 0, leadingTerm = this->getLeadingCoef();
    for(int i = 0; i < this->nr_monoame; ++i) // caut coeficientul termenului constant, daca nu apare in array u de monoame inseamna ca e zero
        if(this->monoame[i].getGrad() == 0)
        {
            constTerm = this->monoame[i].getCoef();
        }
        else if(this->monoame[i].getGrad() > 0)
            break;
    buildFactors(constTerm, constFactors);
    buildFactors(leadingTerm, leadingFactors);

    std::set<int>::iterator it = constFactors.begin();
    bool foundValue = false;
    float correctVal;
    for(; it != constFactors.end() && !foundValue; it++)
    {
        std::set<int>::iterator it_l = leadingFactors.begin();
        for(; it_l != leadingFactors.end() && !foundValue; ++it_l)
        {
            if(this->plugInNumber((float)(*it)/(float)(*it_l)) == 0)
            {
                foundValue = true;
                correctVal = (float)(*it)/(float)(*it_l);
                break;
            }
        }

    }
    if(foundValue == false)
    {
        //std::cout << "Nu au fost gasita o factorizare cu radacini rationale.\n";
        std::vector<Polinom*> ret;
        ret.push_back(new Polinom(*this));
        return ret;
    }
    // daca am ajuns aici, avem o radacina in correctVal
    // tot ce ramane de facut e de construit un polinom de grad 1 de forma x - correctVal si sa impart polinomu original la el
    Polinom* first_factor = new Polinom;
    first_factor->addMonom(Monom(correctVal == 0 ? -INF : 0, -correctVal));
    first_factor->addMonom(Monom(1, 1));

    if(*first_factor == *this){
        std::vector<Polinom*> ret;
        ret.push_back(new Polinom(*this));
        this->avoidLeaks = ret;
        return ret;
    }

    Polinom* second_factor = new Polinom;
    *second_factor = ((*this) / (*first_factor)).first;
    std::vector<Polinom*> ret;
    ret.push_back(first_factor);
    ret.push_back(second_factor);
    this->avoidLeaks = ret;
    return ret;
}


void Polinom::showReducedForm()
{
    this->reducedForm();
    std::vector<Polinom*> redForm = this->reducedForm();
    for(std::vector<Polinom*>::iterator it = redForm.begin(); it != redForm.end(); ++it)
    {
        std::cout << "(" << (**it) << ")";
    }
}

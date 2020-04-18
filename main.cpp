#include <iostream>
#include <Polinom_ireductibil.h>
using namespace std;

int main()
{
    Polinom p, q;
    cin >> p >> q;
    (p + q).showReducedForm(); cout << endl;
    Polinom_ireductibil pi = p + q;
    cout << pi << endl;
    cin >> pi;
    cout << p << '\n' <<p.iredEinstein() << '\n';
    cout << pi << ' ' << p + pi << '\n';
    p.showReducedForm();cout << endl;
    pi.showReducedForm();
    return 0;
}

#include <iostream>
#include <Polinom_ireductibil.h>
using namespace std;

int main()
{
    Polinom p;
    cin >> p;
    Polinom_ireductibil pi;
    cin >> pi;
    cout << p << '\n' <<p.iredEinstein() << '\n';
    cout << pi << ' ' << p + pi << '\n';
    p.showReducedForm();cout << endl;
    pi.showReducedForm();
    return 0;
}

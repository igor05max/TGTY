#include <iostream>
using namespace std;

/*
 Задание 1
*/
int main() {

    setlocale(LC_ALL, "Russian");
    // a)
    cout << "a)" << endl;
    double summ = 1000;
    for (int i = 1; i <= 10; ++i) {
        double res = summ * .02;
        cout << "прирост за " << i << " месяц " << res << endl;
        summ += res;
    }

    // б)
    cout << "б)" << endl;
    summ = 1000;
    for (int i = 1; i <= 10; ++i) {
        summ *= 1.02;
        cout << "сумма вклада через " << i << " мес. " << summ << endl;
    }
    

    return 0;
}

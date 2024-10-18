#include <iostream>

using namespace std;

/*
 Задание 2
*/
int main() {

    setlocale(LC_ALL, "Russian");
    
    // a)
    cout << "a)" << endl;
    double territory = 100, profit = 20;
    for (int i = 2; i <= 8; ++i) {
        profit *= 1.02;
        cout << "урожайность за " << i << " год = " << profit << endl;
    }

    // б)
    cout << "б)" << endl;
    for (int i = 2; i <= 7; ++i) {
        territory *= 1.05;
        if (i >= 4)
            cout << "площадь участка за " << i << " год = " << territory << endl;
    }

    // в) 
    cout << "в)" << endl;
    territory = 100, profit = 20;
    double summ = profit * territory;
    for (int i = 2; i <= 6; ++i) {
        profit *= 1.02;
        territory *= 1.05;
        summ += profit * territory;
    }
    cout << "урожай за первые шесть лет: " << summ << endl;

    return 0;
}

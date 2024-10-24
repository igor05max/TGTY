#include <iostream>

using namespace std;


int main() {

    setlocale(LC_ALL, "Russian");
    
    bool ts = true;
    int contl = 0;

    for (int i = 1; i <= 25; ++i) {
        if (ts)
            cout << i << "\t";
        else {
            cout << i + contl << "\t";
            contl -= 2;
        }
        if (i % 5 == 0) {
            cout << endl;
            ts = !ts;
            contl = 4;
        }
    }
    return 0;
}

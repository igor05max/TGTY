#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));

    int mass[50];
    for (int i = 0; i < 50; i++)
        mass[i] = rand() % 2;

    int count_1 = 0;
    for (int i : mass) {
        count_1 += i;
    }

    for (int i : mass) cout << i << " ";
    cout << "\n";


    cout << "count 1: " << count_1 << "\n" << "count 0: " << 50 - count_1;

    return 0;

}


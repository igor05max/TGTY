#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));


    int count_1 = 0;
    for (int i = 0; i < 50; i++) {
        int x = rand() % 2;
        count_1 += x;
        cout << x << " ";
    }
    cout << "\n";


    cout << "count 1: " << count_1 << "\n" << "count 0: " << 50 - count_1;

    return 0;

}

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));

    int n = rand() % 20 + 1;
    int m = rand() % 20 + 1;

    cout << "n: " << n << " m: " << m << "\n";

    int a, b;
    cin >> a >> b;

    for (int i = 0; i < n; i++)
        cout << rand() % (b - a + 1) + a << " ";
    cout << "\n";

    for (int i = 0; i < m; i++) {
        cout << (rand() % (n * 1000 + 1)) * 0.001 << " ";
    }

    return 0;

}


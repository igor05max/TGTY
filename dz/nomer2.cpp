#include <iostream>
#include <vector>

using namespace std;



int main() {
    /*
    * 0 ->
    * 1 V
    * 2 <-
    * 3 ^
    */

    setlocale(LC_ALL, "Russian");
    
    vector<vector<int>> mass(5, { 0, 0, 0, 0, 0 });

    bool run = true;

    int i = 0, j = -1;
    vector<vector<int>> orint = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };
    
    int orint_index = 0;
    int ai = orint[orint_index][0], aj = orint[orint_index][1];
    int hod = 0;
    
    while (true) {
        
        if (0 <= i + ai && i + ai < 5 && 0 <= j + aj && j + aj < 5 && mass[i + ai][j + aj] == 0) {
            hod++;
            mass[i + ai][j + aj] = hod;
            run = true;
            i += ai;
            j += aj;

        }
        else if (!run) {
            break;
        }
        else {
            orint_index = (orint_index + 1) % 4;
            ai = orint[orint_index][0];
            aj = orint[orint_index][1];
            run = false;
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << mass[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}

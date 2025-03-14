#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char ifname[20]; 
    char ofname[20]; 

    cout << "Введите имя исходного файла: ";
    cin >> ifname;


    FILE* inputFile = fopen(ifname, "r");
    if (!inputFile) {
        cerr << "Ошибка открытия файла. Возможно файл отсутствует: " << ifname << endl;
        return 1;
    }


    char str[100]; 
    int strNumber = 0; 
    int res = 0;

    while (fgets(str, sizeof(str), inputFile)) {
        int countI = 0;
        for (char ch : str) {
            if (ch == 'и' || ch == 'И')
                countI++;
        }
        if (countI == 5)
            res++;
    }

    
    fclose(inputFile);

    cout << res << endl;

    return 0;
}

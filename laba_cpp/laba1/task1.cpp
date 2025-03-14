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

    cout << "Введите имя результирующего файла: ";
    cin >> ofname;

    FILE* inputFile = fopen(ifname, "r");
    if (!inputFile) {
        cerr << "Ошибка открытия файла. Возможно файл отсутствует: " << ifname << endl;
        return 1;
    }

    
    FILE* outputFile = fopen(ofname, "w");
    if (!outputFile) {
        cerr << "Ошибка открытия файла. Возможно файл отсутствует: " << ofname << endl;
        fclose(inputFile); 
        return 1;
    }

    char str[100]; 
    int strNumber = 0; 

    while (fgets(str, sizeof(str), inputFile)) {
        strNumber++; 
        fputs(str, outputFile); 

        
        if (strNumber == 5) {
            fputs("------------\n", outputFile);
        }
    }

    
    fclose(inputFile);
    fclose(outputFile);

    cout << "OK" << endl;

    return 0;
}

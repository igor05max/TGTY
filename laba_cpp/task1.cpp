#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <conio.h>

using namespace std;



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
    char ifname[20];
    char ofname[20];
    
	FILE* fw;
	cout << "Введите имя файла: ";
	cin >> ifname;
	fw = fopen(ifname, "wb");

	cout << "Введите имя 2го файла: ";
	cin >> ofname;

    FILE* inputFile = fopen(ifname, "r");
    if (!inputFile) {
        cerr << "Ошибка открытия файла. Возможно файл отсутствует. " << ifname << endl;
        return 1;
    }

    FILE* outputFile = fopen(ofname, "w");
    if (!outputFile) {
        cerr << "Ошибка открытия файла. Возможно файл отсутствует. " << ofname << endl;
        fclose(inputFile);
        return 1;
    }

    char str[100]; 
    int strNumber = 0;

    while (fgets(str, sizeof(str), inputFile)) {
        strNumber++;
        if (strNumber == 5) 
            fputs("------------\n", outputFile);
        fputs(str, outputFile);
    }

	return 0;
}

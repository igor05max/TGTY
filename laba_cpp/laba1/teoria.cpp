#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <conio.h>

using namespace std;

int main(int argc, char** argv) {    
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
		
	// Дан типизированный файл, элементами которого 
	// являются отдельные слова.
	// Вывести все слова, начинающиеся на букву 'с'
/*
	// Создание типизированного файла из слов
	char slovo[20];
	char fname[20];
	FILE * fw;
	cout << "Введите имя файла: ";
	cin >> fname;
	fw = fopen(fname, "wb");
	cout << "Введите слово: ";
	cin >> slovo;
	while(slovo[0] != '0') {
		// size_t fwrite (const void * pbuf, size_t size, size_t count, FILE * filestream);
		// fwrite() используется для записи в файл блоков данных любого типа
		// size_t - целые числа без знака
		// первый параметр - указатель на массив данных
		// второй параметр - размер (в байтах) элемента массива
		// третий параметр - количество элементов для записи
		// четвертый параметр - указатель на файл
		// возвращает количество успешно записанных элементов
		fwrite(slovo, sizeof(char), 20, fw);
		cout << "Введите еще слово (для отмены введите 0): ";
		cin >> slovo;
	}
	fclose(fw);	
*/	
/*
	// Решение задачи
	char slovo[20];
	char fname[20];
	FILE * fw;
	cout << "Введите имя файла: ";
	cin >> fname;
	fw = fopen(fname, "rb");
	while(!feof(fw)) {
		// size_t fread (void * pbuf, size_t size, size_t count, FILE * filestream);
		// fread() используется для чтения из файла блока данных любого типа
		// первый параметр - указатель на массив для считываемых данных
		// размер массива >= size * count (байт)
		// второй параметр - размер (в байтах) каждого считываемого элемента
		// третий параметр - количество элементов для чтения
		// четвертый параметр - указатель на файл 
		// возвращает количество успешно считанных элементов
		// количество считанных элементов отличается от заданного количества
		// в случае ошибки чтения или при достижении конца файла
		if(fread(slovo, sizeof(char), 20, fw) == 20) {
 			if((slovo[0] == 'с') || (slovo[0] == 'С')) {
			  cout << slovo << "\n";
	  	}
		}
	}	
	fclose(fw);
*/	
	// В типизированном файле записаны названия городов 
	// и их численность населения.
	// Увеличить численность каждого города на 5%
	// Количество жителей - всегда целое число	
/*
	// Создание типизированного файла
	const int ESC = 27;
	char city[30];
	unsigned int numP;
	char fname[20];
	int req = 0;
	FILE * fc;
	cout << "Введите имя файла: ";
	cin >> fname;
	fc = fopen(fname, "wb");	
	while(req != ESC) {
		cout << "\n\nВведите название города: ";
		cin >> city;
		fwrite(city, sizeof(char), 30, fc);
		cout << "Введите численность населения города: ";
		cin >> numP;
		fwrite(&numP, sizeof(unsigned int), 1, fc);
		cout << "\nДля продолжения записи нажмите любую клавишу, для завершения - ESC:\n";
		// getch() считывает символ со стандартного потока ввода
		req = getch();	
	}
	cout << "\n\nФайл "<< fname <<" создан.\n";
	fclose(fc);	
*/
/*
	// Решение задачи
	char city[30];
	unsigned int numP;
	char fname[20];
	FILE * fc, * fb;
	cout << "Введите имя файла: ";
	cin >> fname;
	fc = fopen(fname, "rb");
	fb = fopen("buf.sts", "wb");
	cout << "Исходные данные из файла: \n";	
	while(!feof(fc)) {
		if(fread(city, sizeof(char), 30, fc) == 30) {
			cout << "Численность населения города " << city << " составляет ";
			fwrite(city, sizeof(char), 30, fb);			
		}		
		if(fread(&numP, sizeof(unsigned int), 1, fc) == 1) {
			cout << numP << " человек.\n";
			numP *= 1.05;
			fwrite(&numP, sizeof(unsigned int), 1, fb);
		}		
	}	
	fclose(fc);
	fclose(fb);	
	remove(fname);	
	rename("buf.sts", fname);
	fc = fopen(fname, "rb");
	cout << "\nДанные из файла после обработки: \n";	
	while(!feof(fc)) {
		if(fread(city, sizeof(char), 30, fc) == 30) {
			cout << "Численность населения города " << city << " составляет ";		
		}
		if(fread(&numP, sizeof(unsigned int), 1, fc) == 1) {
			cout << numP << " человек.\n";
		}		
	}	
	fclose(fc);	
*/	
	// Имеются два типизированных файла одинакового размера, 
	// элементами которых являются числа.
	// Получить третий файл, каждый элемент которого равен 
	// произведению соответствующих элементов заданных файлов.
/*	
	// Создание типизированного числового файла
	const int N = 20;
	double num[N];
	char fname[20];
	FILE * fn;
	cout << "Введите имя файла: ";
	cin >> fname;
	fn = fopen(fname, "wb");
	srand(time(0));
	for(int i = 0; i < N; i++) {
		num[i] = (double)(rand()%1001)/((double)(rand()%101)+1);
		cout << num[i] << endl;
	}
	fwrite(num, sizeof(double), N, fn);
	fclose(fn);	
*/
/*
	// Решение задачи
	const int N = 20;
	double num1[N], num2[N], num3[N];
	char fname[20];
	FILE *fn1, *fn2, *fn3;
	cout << "Введите имя первого файла: ";
	cin >> fname;
	fn1 = fopen(fname, "rb");
	cout << "Введите имя второго файла: ";
	cin >> fname;
	fn2 = fopen(fname, "rb");
	cout << "Введите имя третьего файла: ";
	cin >> fname;
	fn3 = fopen(fname, "wb");
	if(fread(num1, sizeof(double), N, fn1) == N) {
		cout << "Содержимое первого файла считано.\n";		
	}
	if(fread(num2, sizeof(double), N, fn2) == N) {
		cout << "Содержимое второго файла считано.\n";		
	}
	fclose(fn1);
	fclose(fn2);
	for(int i = 0; i < N; i++) {
		num3[i]=num1[i]*num2[i];
	}
	if(fwrite(num3, sizeof(double), N, fn3) == N) {
		cout << "Содержимое третьего файла сформировано.\n";		
	}
	fclose(fn3);
	fn3 = fopen(fname, "rb");
	if(fread(num3, sizeof(double), N, fn3) == N) {
		cout << "Результат:\n";
		printf("%11s %11s %11s \n","file1","file2","file3"); 
		for(int i = 0; i < N; i++) {
			printf("%11.4f %11.4f %11.4f \n",num1[i],num2[i],num3[i]);
		}		
	}
	fclose(fn3);
*/	
	
	// XOR-шифратор
	const int KEY_ONE = 49;
	const int KEY_TWO = 50;
	const int KEY_EXIT = 51;
	char key;
	char fname[20];
	char ch;
	int req = 0;
	FILE *f, *fb;
	cout << "1. Зашифровать файл.\n";
	cout << "2. Расшифровать файл.\n";
	cout << "3. Выход.\n";
	req = getch();
	system("cls");
	while(req != KEY_EXIT) {
		switch(req) {
		case KEY_ONE:
			system("cls");
			cout << "Шифрование.\n";			
			cout << "Введите имя файла: ";
			cin >> fname;
			cout << "Введите ключ (0..255): ";
			cin >> key;
			f = fopen(fname, "rb");
			fb = fopen("buf.xor", "wb");
			// int fgetc( FILE * filestream )
			// fgetc() возвращает символ из указанного файлового потока 
			// при достижении конца файла или ошибки чтения возвращает EOF
			ch = (char)fgetc(f);
			do {
				ch ^= key;
  			// int fputc( int character, FILE * filestream )
	  		// fputc() записывает символ в указанный файловый поток 
		  	// возвращает записанный символ, а в случае ошибки - EOF
				fputc(ch, fb);	
				ch = (char)fgetc(f);			 
			} while(!feof(f));
			fclose(f);
			fclose(fb);
			remove(fname);
			rename("buf.xor", fname);
			cout << "Файл зашифрован.\n";				
			getch();
			break;
		case KEY_TWO:
			system("cls");	
			cout << "Дешифрование.\n";			
			cout << "Введите имя файла: ";
			cin >> fname;
			cout << "Введите ключ (0..255): ";
			cin >> key;
			f = fopen(fname, "rb");
			fb = fopen("buf.xor", "wb");
			ch = (char)fgetc(f);
			do {
				ch ^= key;
				fputc(ch, fb);	
				ch = (char)fgetc(f);			 
			} while(!feof(f));
			fclose(f);
			fclose(fb);
			remove(fname);
			rename("buf.xor", fname);
			cout << "Файл расшифрован.\n";				
			getch();
			break;
		}
		system("cls");
		cout << "1. Зашифровать файл.\n";
		cout << "2. Расшифровать файл.\n";
		cout << "3. Выход.\n";
		req = getch();		
	}
	
	return 0;
}








#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

int fcopy(const char*, const char*);
int fswap(const char*, const char*);

int main(int argc, char** argv) {	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
/*
	// Ex01.
	char str[50];
	// FILE* указатель (дескриптор) файла
	// указывает на структуру типа FILE
	// структура содержит информацию о файле
	FILE *fp;	
	// FILE * fopen(const char * filename, const char * mode)
	// fopen() открывает поток, связывает его с файлом и
	// возвращает указатель на файл
	// первый параметр - имя файла; 
	// второй параметр - режим открытия файла,
	// определяет набор разрешенных операций с файлом
	// Основные режимы:
	// r - открыть текстовый файл для чтения;
	// w - создать текстовый файл для записи;
    // а - добавить записи в конец текстового файла;
    // rb - открыть бинарный файл для чтения;
    // wb - создать бинарный файл для записи;
	// ab - добавить записи в конец бинарного файла;
	fp = fopen("info.txt", "r");
	// fopen() возвращает NULL, если файл открыть не удалось
	if(fp == NULL) {
		cout << "Ошибка открытия файла. Возможно файл отсутствует.\n";
		return 0;
	}
	cout << "Содержимое файла info.txt: \n";
	// int feof(FILE *fp)
	// feof() используется для определения конца файла
	// если достигнут конец файла - возвращает ненулевое значение, 
	// иначе - 0
	while(!feof(fp)) {
		// char * fgets (char * str, int num, FILE * fp)
		// fgets() считывает строку из указанного потока, 
		// пока не обнаружит символ новой строки 
		// или не прочитает заданное количество символов.
		// автоматически добавляет нулевой символ.
		// первый параметр - указатель на считанную строку;
		// второй параметр - максимальное количество символов для чтения,
		// включая нулевой символ;
		// третий параметр - указатель на файл.
		// возвращает указатель на введенную строку 
		// или NULL при возникновении ошибки.
		if(fgets(str, 50, fp) != NULL) {
			cout << str;	
		}
		else {
			cout << "Произошла ошибка при чтении из файла.\n";
			return 0;
		}
	}
	// int fclose(FILE * fp)
	// fclose() записывает все оставшиеся в буфере данные в файл
	// и закрывает поток, связанный с указанным параметром
	fclose(fp);
*/
/*
	// Ex02. Дан текстовый файл. Подсчитать количество символов в каждой строке.
	char str[80];
	FILE *fp;
	int n = 1;
	fp = fopen("info.txt", "r");
	if(fp == NULL) {
		cout << "Ошибка открытия файла. Возможно файл отсутствует.\n";
		return 0;
	}
	while(!feof(fp)) {
		if(fgets(str, 80, fp) != NULL) {
			cout << "Длина строки " << n++ << ": " << strlen(str) - 1 << " символ(а/ов).\n";	
		} 
		else {
			cout << "Произошла ошибка при чтении из файла.\n";
			return 0;
		}
	}
	fclose(fp);
*/
/*
	// Ex03. Имеется текстовый файл. Определить длину самой короткой строки.
	char str[80];
	FILE *fp;
	int minL = 80;
	fp = fopen("info.txt", "r");
	if(fp == NULL) {
		cout << "Ошибка открытия файла. Возможно файл отсутствует.\n";
		return 0;
	}
	while(!feof(fp)) {
		if(fgets(str, 80, fp) != NULL) {
			int l = strlen(str) - 1; 
			if(l < minL) {
				minL = l;
			}
		} 
		else {
			cout << "Произошла ошибка при чтении из файла.\n";
			return 0;
		}
	}
	cout << "Длина самой короткой строки: " << minL << " символ(а/ов).\n";
	fclose(fp);
*/
	
	// Ex04.
    // Имеются два текстовых файла с одинаковым количеством строк.
    // Переписать с сохранением порядка следования строки первого файла во второй, а строки второго - в первый.
    // Использовать вспомогательный файл.
    
	//if(fswap("file1.txt", "file2.txt") < 0) cout << "Произошла ошибка обмена содержимого файлов. \n";

	// int rename( const char * oldfilename, const char * newfilename )
	// rename() изменяет имя существующего файла на новое (или перемещает)
	rename("file2.txt", "swap.txt");
	rename("file1.txt", "file2.txt");
	rename("swap.txt", "file1.txt");
	
	return 0;
}

int fcopy(const char *fName1, const char *fName2) {
	char str[80];
	FILE *f1, *f2;
	f1 = fopen(fName1, "r");
	if(f1 == NULL) {
		cout << "Ошибка открытия файла. Возможно файл отсутствует.\n";
		return -1;
	}
	f2 = fopen(fName2, "w");
	if(f1 == NULL) {
		cout << "Ошибка открытия файла. Возможно файл нельзя создать.\n";
		return -1;
	}
	while(!feof(f1)) {
		if(fgets(str, 80, f1) != NULL) {
			// int fputs (const char * str, FILE * fp);
			// fputs() записывает в заданный поток строку, 
			// на которую ссылается указатель 
			// нулевой символ в файл не копируется 
			// первый параметр - указатель на строку для записи;
			// второй параметр - указатель на файл.
			// возвращает неотрицательное значение в случае успеха или
			// константу EOF при возникновении ошибки
			if(fputs(str, f2) == EOF) {
				cout << "Произошла ошибка записи в файл.\n";
				return -1;
			}	  			
		} 
		else {
			cout << "Произошла ошибка при чтении из файла.\n";
			return -1;
		}
	}
	fclose(f1);
	fclose(f2);
  return 1;
}
	
int fswap(const char *fName1, const char *fName2)	{
	if (fcopy(fName1, "swap.txt") < 0) return -1;
	if (fcopy(fName2, fName1) < 0) return -1;
 	if (fcopy("swap.txt", fName2) < 0) return -1;
	// int remove( const char * fname );
	// remove() удаляет файл с указанным именем
	remove("swap.txt");	
	return 1;
}



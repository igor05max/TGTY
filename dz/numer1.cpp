#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
/*

*/

void new_list(vector<vector<int>> &mass, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mass[i][j] = rand() % 10 + 1;
		}
	}

}

/*

*/
void print(vector<vector<int>> mass) {
	for (int i = 0; i < mass.size(); ++i) {
		for (int j = 0; j < mass[0].size(); ++j) {
			cout << mass[i][j] << "\t";
		}
		cout << endl;
	}
}


void task() {
	vector<vector<int>> mass(12, vector<int>(10));
	new_list(mass, 12, 10);
	for (int i = 1; i <= 12; ++i) {
		for (int j = i * 10, jj = 0; j >= i * 10 - 9; --j, ++jj) {
			mass[i - 1][jj] = j;
		}	
	}
	print(mass);
}
/*
№2
В двумерном массиве хранится информация о количестве учеников
в каждом классе каждой параллели школы с первой по одиннадцатую
(в первой строке — информация о классах первой параллели, во второй — второй параллели и т. д.). 
В каждой параллели школы имеются четыре класса. Определить общее число учеников в параллели 5-х классов.*/

void task2() {
	vector<vector<int>> mass(11, vector<int>(4));
	new_list(mass, 11, 4);
	print(mass);

	int res = 0;
	for (int i = 0; i < 4; ++i)
		res += mass[4][i];
	cout << res << endl;
}

/*
№3
нахождения номера столбца,
в котором расположен минимальный элемент любой строки двумерного массива.
Если элементов с минимальным значением в этой строке несколько, 
то должен быть найден номер столбца самого левого из них.
*/
void task3() {
	vector<vector<int>> mass(10, vector<int>(10));
	new_list(mass, 10, 10);
	print(mass);

	int i_best = 0;
	for (int i = 1; i < 10; ++i) {
		if (mass[i][2] >= mass[i_best][2])
			i_best = i;
	}
	cout << i_best + 1 << endl;
}

/*
№4
нахождения номера столбца, 
в котором расположен минимальный элемент любой строки двумерного массива. 
Если элементов с минимальным значением в этой строке несколько, 
то должен быть найден номер столбца самого левого из них.
*/
void task4() {
	vector<vector<int>> mass(10, vector<int>(10));
	new_list(mass, 10, 10);
	print(mass);
	
	int j_best = 10;
	for (int i = 0; i < 10; ++i) {
		int j_min = 0;
		for (int j = 1; j < 10; ++j) {
			if (mass[i][j] < mass[i][j_min])
				j_min = j;
		}
		j_best = min(j_min, j_best);
	}
	cout << j_best + 1 << endl;

}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	//task();
	//task2();
	//task3();
	task4();



	return 0;

}

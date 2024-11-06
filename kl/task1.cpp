#include <iostream>
#include <vector>

using namespace std;

/*
Дан массив из четного числа
элементов. Поменять местами его
половины;*/
void task() {
	int n;
	cin >> n;
	vector<int> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}

	for (int i = 0; i < n / 2; ++i)
		swap(mass[i], mass[i + n / 2]);

	for (int i = 0; i < n; ++i)
		cout << mass[i] << " ";

}


/*
Дан массив целых чисел. Найти
номер первого нечетного элемента.
Если нечетных элементов в массиве
нет, то должно быть выведено
соответствующее сообщение;*/
void task2() {
	int n;
	cin >> n;
	vector<int> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}
	for (int i = 0; i < n; ++i) {
		if (mass[i] % 2 == 1) {
			cout << i + 1;
			return;
		}
	}
	cout << "нет такого числа";
}


/*
Даны два массива одного размера. Получить
третий массив, каждый четный элемент
которого равен произведению элементов с
тем же номером в заданных массивах, а
каждый нечетный – сумме элементов с тем
же номером в заданных массивах*/
void task3() {
	int n;
	cin >> n;
	vector<int> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}

	vector<int> mass2(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass2[i];
	}

	vector<int> res(n);
	for (int i = 0; i < n; ++i) {
		if (i % 2 == 0)
			res[i] = mass[i] * mass2[i];
		else
			res[i] = mass[i] + mass2[i];
	}
	for (int i = 0; i < n; ++i) {
		cout << res[i] << " ";
	}
}


/*
Дан массив вещественных
чисел. Выяснить, верно ли,
что минимальный элемент
меньше максимального
более чем в два раза*/

void task4() {
	int n;
	cin >> n;
	vector<double> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}
	double mx = DBL_MIN, mn = DBL_MAX;
	for (double x : mass) {
		mx = max(x, mx);
		mn = min(x, mn);
	}
	if (mn * 2 < mx) {
		cout << "yes";
	}
	else {
		cout << "no";
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	/*task1();
	task2();
	task3();*/
	task4();

	return 0;

}

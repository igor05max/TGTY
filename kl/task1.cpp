#include <iostream>
#include <cmath>
using namespace std;


bool ekh(int s) {
	int sum1 = s % 10 + s / 10 % 10 + s / 100 % 10;
	int sum2 = s / 1000 % 10 + s / 1000 / 10 % 10 + s / 1000 / 100 % 10;
	return sum1 == sum2;
}



int dest(double a, double b, double c) {
	double d;
	d = b * b - 4 * a * c;
	return int(d >= 0);
}



int nod(int a, int b) {
	while (a != 0 && b != 0) {
		if (a > b) {
			a = a % b;
		}
		else {
			b = b % a;
		}
	}
	return a + b;
}

/*
Даны три квадратных уравнения
ax2 + bx + c,
bx2 + ax + c,
cx2 + ax + b.
Сколько из них имеют действительные корни. (Определить функцию, позволяющую
распознавать наличие действительных корней в квадратном уравнении.)
*/
void task1() {
	double a, b, c; cin >> a >> b >> c;
	int res = 0;
	res += dest(a, b, c);
	res += dest(b, a, c);
	res += dest(c, a, b);
	cout << res << endl;
}

/*
Даны натуральные числа a и b, обозначающие соответственно числитель и знаменатель дроби.
Сократить дробь, т.е. найти такие натуральные числа p и q, не имеющие общих делителей, что
p/q = a/b. Определить функцию для расчета наибольшего общего делителя двух натуральных
чисел, используя алгоритм Евклида;
*/
void task2() {
	int a, b; cin >> a >> b;
	int delit = nod(a, b);
	cout << a / delit << " " << b / delit << endl;;

}

void upString(int x) {
	int a = 1;
	int res = 0;
	for (int length = 1; length <= 8; length++) {
		a *= 10;

		if (a > x) {
			res = length;
			break;
		}
	}
	for (int i = 0; i < 6 - res - 1; i++) {
		cout << "0";
	}
	cout << x << endl;
}

/*
Получить все шестизначные счастливые номера. Счастливым называют такое шестизначное
число, в котором сумма его первых трех цифр равна сумме его последних трех цифр.
(Определить функцию для расчета суммы цифр трехзначного числа.)
*/
void task3() {

	for (int x = 0; x <= 999999; x++) {
		if (ekh(x)) upString(x);
	}
}


double z(double a, double b, double x, double y) {
	return (((a + y) / 4) + ((b + x) / 4)) / (((y - x) / 4) + ((b + a) / 4)) - ((sin(a) * cos(b)) / (sin(y) * sin(x)));
}


void task4() {
	double a, b, x, y;
	cin >> a >> b >> x >> y;
	cout << z(a, b, x, y);
}


int main() {

	setlocale(LC_ALL, "RU");
	task4();

	return 0;
}

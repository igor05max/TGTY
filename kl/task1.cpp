#include <iostream>
#include <vector>

using namespace std;

/*
��� ������ �� ������� �����
���������. �������� ������� ���
��������;*/
void task() {
	int n;
	cin >> n;
	vector<int> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}

	for (int i = 0; i < n / 2; ++i)
		swap(mass[i], mass[n - i - 1]);

	for (int i = 0; i < n; ++i)
		cout << mass[i] << " ";

}


/*
��� ������ ����� �����. �����
����� ������� ��������� ��������.
���� �������� ��������� � �������
���, �� ������ ���� ��������
��������������� ���������;*/
void task2() {
	int n;
	cin >> n;
	vector<int> mass(n);
	for (int i = 0; i < n; ++i) {
		cin >> mass[i];
	}
	for (int i = 0; i < n; ++i) {
		if (mass[i] % 2 == 1) {
			cout << i;
			return;
		}
	}
	cout << "��� ������ �����";
}


/*
���� ��� ������� ������ �������. ��������
������ ������, ������ ������ �������
�������� ����� ������������ ��������� �
��� �� ������� � �������� ��������, �
������ �������� � ����� ��������� � ���
�� ������� � �������� ��������*/
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
��� ������ ������������
�����. ��������, ����� ��,
��� ����������� �������
������ �������������
����� ��� � ��� ����*/

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
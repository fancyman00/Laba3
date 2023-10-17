#include<iostream>
#include<Windows.h>
#include<iomanip>
#include <functional>
using std::cin;
using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;
using std::function;


void print_answer(const char* message, double s);
double sum_series(double x, int n);
double sum_series(double x, double eps, int *i);
int main_menu();
template <typename T, typename F>
void read_and_check(T& x, F condition, const char* message);

int main()
{
	SetConsoleOutputCP(1251);
	short choice;
	double sum;
	do
	{
		choice = main_menu();

		if (choice != 3)
		{
			double x;
			char isExit;
			read_and_check<double, function<bool(double)>>(
				x,
				[](double x) -> bool {return abs(x) < 1; },
				"������� x (|x|<1): ");
			if (choice == 1)
			{
				int n;
				cout << "������� ���������� ���������: ";
				cin >> n;
				sum = sum_series(x, n);
			}
			else
			{
				double eps;
				cout << "������� �������� ���������� = ";
				cin >> eps;
				int count = 0;
				sum = sum_series(x, eps, &count);
				print_answer("���������� ���������", count);
			}
			print_answer("������ ��������", 1 / (1 + x));
			print_answer("������������ ��������", sum);
			cout << "��������� ������? (Y(y) , ����� ������ ������� - ���������� ������): ";
			cin >> isExit;
			if (isExit == 'Y' || isExit == 'y')
				choice = 3;
		}
	} while (choice != 3);
	return 0;
}


template <typename T, typename F>
void read_and_check(T& x, F condition, const char* message) {
	cout << message;
	while (!(cin >> x && condition(x)))
	{
		cout << "������ �����!" << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << message;
	}

}

void print_answer(const char* message, double sum)
{
	cout << setw(28) << left << message << " = " << fixed << setprecision(11) << sum << endl;
}

int main_menu() {
	cout << "����" << endl;
	cout << "1. ����� ��������� ���������� ���������" << endl;
	cout << "2. ����� � �������� ���������" << endl;
	cout << "3. ���������� ������" << endl;
	function<bool(int)> Lambda = [](int x) -> bool
	{
		return x >= 1 && x <= 3;
	};
	int choise{};
	read_and_check<int, function<bool(int)>>(choise, Lambda, "-> ");
	return choise;
}

double sum_series(double x, int n)
{
	double a = 1, sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += a;
		a *= (-x);
	}
	return sum;
}

double sum_series(double x, double eps, int *n)
{
	double a = 1, sum = 0;
	for (int i = 0; i < 2; ++i)
	{
		while (abs(a) > eps)
		{
			sum += a;
			a *= (-x);
			*n += 1;
		}
		return sum;
	}
}
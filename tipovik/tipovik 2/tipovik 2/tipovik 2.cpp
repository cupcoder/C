// tipovik 2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"

int n, c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	// Задаем кол - во чисел
	std::cout << "Введите кол-во чисел: ";
	std::cin >> n;

	int *arr = new int[n];

	// Вводим сами числа
	std::cout << "Введите числа: " << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "[" << i+1 <<"]: ";
		std::cin >> arr[i];
	}

	// Считаем соседей с разными знаками
	c = 0;
	for (int j = 0; j < n-1; j++) {
		if (arr[j] * arr[j+1] < 0) c++;
	}

	// Выводим результат каунтера
	std::cout << "Кол - во соседей с разным знаком в данном ряде: " << c << std::endl;
	system("pause");
	delete[] arr; // освобождаем память
	return 0;
}


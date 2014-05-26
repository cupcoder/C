// tipovik 4.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"

int n, m, c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Введите кол-во строк: ";
	std::cin >> n;
	std::cout << "Введите кол-во столбцов: ";
	std::cin >> m;
	int **a;
	a = new int*[n]; // Выделение памяти для массива
	int *el = new int[n];

	//Заполняем матрицу
	for (int i = 0; i < n; i++) {
		a[i] = new int[m];
		for (int j = 0; j < m; j++) {
			std::cout << "Введите элемент [" << i + 1 << "][" << j + 1 << "]: ";
			std::cin >> a[i][j];
		}
	}

	//Находим минимальные элементы в строках
	for (int i = 0; i < n; i++) {
		el[i] = a[i][0];
		for (int j = 0; j < m; j++) {
			if (el[i] > a[i][j]) el[i] = a[i][j];
		}
	}

	// Находим максимальный элемент в массиве
	c = el[0];
	for (int i = 0; i < n; i++) {
		if (c < el[i]) c = el[i];
	}

	// Выводим индексы максимального элемента
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (c == a[i][j]) {
				std::cout << "Индексы максимального элемента: [" << i + 1 << "][" << j + 1 << "]";
			}
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}


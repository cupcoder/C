// tipovik 3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"

int a[6][3], el[6], c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	//Заполняем матрицу
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "Введите элемент [" << i+1 << "][" << j+1 << "]: ";
			std::cin >> a[i][j];
		}
	}

	//Находим минимальные элементы в строках
	for (int i = 0; i < 6; i++) {
		el[i] = a[i][0];
		for (int j = 0; j < 3; j++) {
			if (el[i] > a[i][j]) el[i] = a[i][j];
		}
	}

	// Находим максимальный элемент в массиве
	c = el[0];
	for (int i = 0; i < 6; i++) {
		if (c < el[i]) c = el[i];
	}

	// Выводим индексы максимального элемента
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			if (c == a[i][j]) {
				std::cout << "Индексы максимального элемента: [" << i + 1 << "][" << j + 1 << "]";
			}
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}


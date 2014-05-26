// typovik 1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"

int n = 6, arr[6];

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	// Заполняем массив
	std::cout << "Введите элементы массива" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "[" << i + 1 << "]: ";
		std::cin >> arr[i];
	}
	// Переставляем элементы
	for (int j = 0; j <= 2 % n; j++) {
		// Сохраняем значение одного из элементов в переменной
		int a = arr[j];
		// И производим замену
		arr[j] = arr[n - j - 1];
		arr[n - j - 1] = a;
	}
	// Выводим готовый массив
	std::cout << "Измененный массив:";
	for (int k = 0; k < n; k++) {
		std::cout << " " << arr[k] << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
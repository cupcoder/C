// typovik 1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"

int n = 6, arr[6];

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	// ��������� ������
	std::cout << "������� �������� �������" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "[" << i + 1 << "]: ";
		std::cin >> arr[i];
	}
	// ������������ ��������
	for (int j = 0; j <= 2 % n; j++) {
		// ��������� �������� ������ �� ��������� � ����������
		int a = arr[j];
		// � ���������� ������
		arr[j] = arr[n - j - 1];
		arr[n - j - 1] = a;
	}
	// ������� ������� ������
	std::cout << "���������� ������:";
	for (int k = 0; k < n; k++) {
		std::cout << " " << arr[k] << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
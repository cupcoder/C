// tipovik 2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"

int n, c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	// ������ ��� - �� �����
	std::cout << "������� ���-�� �����: ";
	std::cin >> n;

	int *arr = new int[n];

	// ������ ���� �����
	std::cout << "������� �����: " << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "[" << i+1 <<"]: ";
		std::cin >> arr[i];
	}

	// ������� ������� � ������� �������
	c = 0;
	for (int j = 0; j < n-1; j++) {
		if (arr[j] * arr[j+1] < 0) c++;
	}

	// ������� ��������� ��������
	std::cout << "��� - �� ������� � ������ ������ � ������ ����: " << c << std::endl;
	system("pause");
	delete[] arr; // ����������� ������
	return 0;
}


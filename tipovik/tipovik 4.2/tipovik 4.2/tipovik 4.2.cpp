// tipovik 4.2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"

int n, m, c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	std::cout << "������� ���-�� �����: ";
	std::cin >> n;
	std::cout << "������� ���-�� ��������: ";
	std::cin >> m;
	int **a;
	a = new int*[n]; // ��������� ������ ��� �������
	int *el = new int[n];

	//��������� �������
	for (int i = 0; i < n; i++) {
		a[i] = new int[m];
		for (int j = 0; j < m; j++) {
			std::cout << "������� ������� [" << i + 1 << "][" << j + 1 << "]: ";
			std::cin >> a[i][j];
		}
	}

	//������� ����������� �������� � �������
	for (int i = 0; i < n; i++) {
		el[i] = a[i][0];
		for (int j = 0; j < m; j++) {
			if (el[i] > a[i][j]) el[i] = a[i][j];
		}
	}

	// ������� ������������ ������� � �������
	c = el[0];
	for (int i = 0; i < n; i++) {
		if (c < el[i]) c = el[i];
	}

	// ������� ������� ������������� ��������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (c == a[i][j]) {
				std::cout << "������� ������������� ��������: [" << i + 1 << "][" << j + 1 << "]";
			}
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}


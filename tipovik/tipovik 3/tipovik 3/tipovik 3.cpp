// tipovik 3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"

int a[6][3], el[6], c;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	//��������� �������
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "������� ������� [" << i+1 << "][" << j+1 << "]: ";
			std::cin >> a[i][j];
		}
	}

	//������� ����������� �������� � �������
	for (int i = 0; i < 6; i++) {
		el[i] = a[i][0];
		for (int j = 0; j < 3; j++) {
			if (el[i] > a[i][j]) el[i] = a[i][j];
		}
	}

	// ������� ������������ ������� � �������
	c = el[0];
	for (int i = 0; i < 6; i++) {
		if (c < el[i]) c = el[i];
	}

	// ������� ������� ������������� ��������
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			if (c == a[i][j]) {
				std::cout << "������� ������������� ��������: [" << i + 1 << "][" << j + 1 << "]";
			}
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}


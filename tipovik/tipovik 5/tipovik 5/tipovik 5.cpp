// typovik 5.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"
#include <vector>
#include <string>

std::string str;
int c;
std::vector<char> lit;

char string_EN[26] = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
char string_en[26] = "abcdefghijklmnopqrstuwxyz";

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	// �������� �����
	std::cout << "������� �����: ";
	std::cin >> str;
	std::cout << "��������� ����� ������ � ���� ����� �� ������ ����:";
	// ���������� ������ ����� �� �������� ..
	for (int i = 0; i < 26; i++) {
		c = 0; // �������
		// .. �� ������� ���������� � ������� �� ������
		for (int j = 0; j < str.size(); j++) {
			if (str[j] == string_EN[i] || str[j] == string_en[i]) c++;
		}
		if (c == 1) std::cout << " " << string_en[i]; // ���� ���������� ������ ����, ������� ��� �����
	}
	std::cout <<  std::endl;
	system("pause");
	return 0;
}
// typovik 5.cpp: определяет точку входа для консольного приложения.
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

	// Набираем текст
	std::cout << "Введите текст: ";
	std::cin >> str;
	std::cout << "Следующие буквы входят в этот текст по одному разу:";
	// Перебираем каждую букву из алфавита ..
	for (int i = 0; i < 26; i++) {
		c = 0; // счетчик
		// .. на предмет совпадения с буквами из текста
		for (int j = 0; j < str.size(); j++) {
			if (str[j] == string_EN[i] || str[j] == string_en[i]) c++;
		}
		if (c == 1) std::cout << " " << string_en[i]; // если совпадение только одно, выводим эту букву
	}
	std::cout <<  std::endl;
	system("pause");
	return 0;
}
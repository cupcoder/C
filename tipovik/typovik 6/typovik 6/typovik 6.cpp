// typovik 6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	// ����� ��� ������ � ��������
	class Vector
	{
	public:
		double x1, x2, x3, x4, x5;//���������� �������
		Vector(double y1,double y2,double y3, double y4, double y5)
		{
			x1 = y1;
			x2 = y2;
			x3 = y3;
			x4 = y4;
			x5 = y5;
		}
		void plus(Vector x, Vector y)
		{
			x1 = x.x1 + y.x1;
			x2 = x.x2 + y.x2;
			x3 = x.x3 + y.x3;
			x4 = x.x4 + y.x4;
			x5 = x.x5 + y.x5;
		}
		void minus(Vector x, Vector y)
		{
			x1 = x.x1 - y.x1;
			x2 = x.x2 - y.x2;
			x3 = x.x3 - y.x3;
			x4 = x.x4 - y.x4;
			x5 = x.x5 - y.x5;
		}
		double multiple(Vector x, Vector y)
		{
			x1 = x.x1 * y.x1;
			x2 = x.x2 * y.x2;
			x3 = x.x3 * y.x3;
			x4 = x.x4 * y.x4;
			x5 = x.x5 * y.x5;
			double rez = x1 + x2 + x3 + x4 + x5;
			return rez;
		}

	};

	// ������� ������� ������ ������

	Vector x(0,0,0,0,0);
	Vector y(0,0,0,0,0);
	Vector z(0,0,0,0,0);

	// ������ ���������� ��������

	std::cout << "������� ���������� ������� �" << std::endl;
	std::cin >> x.x1;
	std::cin >> x.x2;
	std::cin >> x.x3;
	std::cin >> x.x4;
	std::cin >> x.x5;
	std::cout << "������� ���������� ������� Y" << std::endl;
	std::cin >> y.x1;
	std::cin >> y.x2;
	std::cin >> y.x3;
	std::cin >> y.x4;
	std::cin >> y.x5;

	// ��������� �������� � ���������, ��������� ������ ������ Vector, � ������� ���������

	std::cout << "��������� �������� \n";
	z.plus(x, y);
	std::cout << z.x1<<","<<z.x2<<","<< z.x3<<","<< z.x4<<","<< z.x5 <<"\n";
	std::cout << "��������� ��������� \n";
	z.minus(x, y);
	std::cout << z.x1 << "," << z.x2 << "," << z.x3 << "," << z.x4 << "," << z.x5 << "\n";
	
	std::cout << "��������� ���������� ������������ \n";
	std::cout <<z.multiple(x,y);
	system("pause");
	return 0;
}


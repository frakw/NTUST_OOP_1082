#include <iostream>
#include "Month.h"

using namespace std;

int main(void)
{
	Month month1, month2(2), month3('M','a','r'), month4, month5, month6;
	month4 = month3.nextMonth();
	month5.inputInt();
	month6.inputStr();

	cout << "Month1 = ";
	month1.outputInt();
	cout << ' ';
	month1.outputStr();
	cout << endl;

	cout << "Month2 = ";
	month2.outputInt();
	cout << ' ';
	month2.outputStr();
	cout << endl;

	cout << "Month3 = ";
	month3.outputInt();
	cout << ' ';
	month3.outputStr();
	cout << endl;

	cout << "Month4 = ";
	month4.outputInt();
	cout << ' ';
	month4.outputStr();
	cout << endl;

	cout << "Month5 = ";
	month5.outputInt();
	cout << ' ';
	month5.outputStr();
	cout << endl;

	cout << "Month6 = ";
	month6.outputInt();
	cout << ' ';
	month6.outputStr();
	cout << endl;
	return 0;
}
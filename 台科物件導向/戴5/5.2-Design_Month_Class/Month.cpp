#include "Month.h"
#include <string>
#include <iostream>
using namespace std;

string month_string[12] = {
"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

Month::Month()
{
	month = 1;
}

Month::Month(char first, char second, char third)
{
	string mon = "";
	mon = mon + first + second + third;
	for (int i = 0;i < 12;i++) {
		if (mon == month_string[i]) {
			month = i + 1;
			break;
		}
	}
}

Month::Month(int monthInt)
{
	month = monthInt;
}


Month::~Month()
{
}

void Month::inputInt()
{
	int montha;

	cin >> montha;

	if (montha > 1 && montha < 13) {
		month = montha;
	}
	else {
		month = 1;
	}
}

void Month::inputStr()
{
	char input;
	string mon = "";
	for (int i = 0;i < 3;i++) {
		cin >> input;
		mon += input;
	}
	for (int i = 0;i < 12;i++) {
		if (mon == month_string[i]) {
			month = i + 1;
			break;
		}
	}

}

void Month::outputInt()
{
	cout << month;
}

void Month::outputStr()
{
	cout << month_string[month - 1];
}

Month Month::nextMonth()
{
	Month result;
	if (month == 12) {
		result.month = 1;
	}
	else {
		result.month = month + 1;

	}
	return result;
}

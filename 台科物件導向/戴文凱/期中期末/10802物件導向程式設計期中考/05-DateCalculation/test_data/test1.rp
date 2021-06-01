#include <iostream>
#include "Date.h"
using namespace std;

int main(void) 
{
	enum COMMAND { GREATER = 1, SMALLER, BETWEEN, D_SUB_N, D_PLUS_N, N_PLUS_D };
	int command, y1, m1, d1, y2, m2, d2, num;
	cin >> command;

	while (command != 0) 
	{
		switch (command)
		{
		case GREATER:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 > date2 ? "true" : "false") << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case SMALLER:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 < date2 ? "true" : "false") << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case BETWEEN:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 - date2) << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case D_SUB_N:
		{
			cin >> y1 >> m1 >> d1 >> num;
			Date date(y1, m1, d1);
			if (date.check()) 
			{
				Date ansDate = date - num;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		case D_PLUS_N:
		{
			cin >> y1 >> m1 >> d1 >> num;
			Date date(y1, m1, d1);
			if (date.check()) 
			{
				Date ansDate = date + num;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		case N_PLUS_D:
		{
			cin >> num >> y1 >> m1 >> d1;
			Date date(y1, m1, d1);
			if (date.check())
			{
				Date ansDate = num + date;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		}
		cin >> command;
	}
	return 0;
}
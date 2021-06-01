#include "Date.h"

const int MONTHS_DAY[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool Date::check()
{
	if (m_year <= YEAR_LIMIT && m_year > 0)
	{
		if (m_month <= 12 && m_month > 0)
		{
			if (m_day <= MONTHS_DAY[m_month - 1] && m_day > 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

Date Date::operator- (const int num)
{
	int n, year, month, day;
	n = num;
	year = m_year;  month = m_month; day = m_day;

	year -= n / 365;
	n = n % 365;
	if (day > n) day -= n;
	else {
		n -= day;
		if (month == 1)
		{
			month = 12;
			year -= 1;
		}
		else month -= 1;
		day = MONTHS_DAY[month - 1];
		while (n >= MONTHS_DAY[month - 1])
		{
			n -= MONTHS_DAY[month - 1];
			if (month == 1)
			{
				month = 12;
				year -= 1;
			}
			else month -= 1;
			day = MONTHS_DAY[month - 1];
		}
		if (n > 0) day -= n;
	}
	return Date(year, month, day);
}

Date Date::operator+ (const int num)
{
	int n, year, month, day;
	n = num;
	year = m_year;  month = m_month; day = m_day;

	year += n / 365;
	n = n % 365;
	day += n;
	while (day > MONTHS_DAY[month - 1])
	{
		day -= MONTHS_DAY[month - 1];
		if (month == 12)
		{
			month = 1;
			year++;
		}
		else month += 1;
	}
	return Date(year, month, day);
}

Date operator+ (const int num, const Date& date)
{
	int n = num;
	Date ansDate = date;
	ansDate.m_year += n / 365;
	n = n % 365;
	ansDate.m_day += n;
	while (ansDate.m_day > MONTHS_DAY[ansDate.m_month - 1])
	{
		ansDate.m_day -= MONTHS_DAY[ansDate.m_month - 1];
		if (ansDate.m_month == 12)
		{
			ansDate.m_month = 1;
			ansDate.m_year++;
		}
		else ansDate.m_month += 1;
	}
	return ansDate;
}

int operator- (const Date& date1, const Date& date2)
{
	int days = 0;	// how many days between two dates
	Date a = date1, b = date2;

	if (date1 < date2)
	{
		a = date2;
		b = date1;
	}

	days += (a.m_year - b.m_year) * 365;
	if (a.m_month > b.m_month)
	{
		for (int i = b.m_month; i < a.m_month; i++)
			days += MONTHS_DAY[i - 1];
		if (a.m_day > b.m_day)
			days += a.m_day - b.m_day;
		else if (a.m_day < b.m_day)
			days -= b.m_day - a.m_day;
	}
	else
	{
		if (a.m_month != b.m_month)
			for (int i = a.m_month; i < b.m_month; i++)
				days -= MONTHS_DAY[i - 1];
		if (a.m_day > b.m_day)
			days += a.m_day - b.m_day;
		else if (a.m_day < b.m_day)
			days -= b.m_day - a.m_day;
	}
	return days;
}

bool operator> (const Date& date1, const Date& date2)
{
	if (date1.m_year > date2.m_year) return true;
	else
	{
		if (date1.m_year == date2.m_year)
		{
			if (date1.m_month > date2.m_month)
				return true;
			else
			{
				if (date1.m_month == date2.m_month)
				{
					if (date1.m_day > date2.m_day)
						return true;
					else
						return false;	// date1.day == date2.day || date1.day < date2.day
				}
				else
					return false;	// date1.month < date2.month
			}
		}
		else
			return false;	// date1.year < date2.year
	}
}

bool operator< (const Date& date1, const Date& date2)
{
	if (date1 > date2)
		return false;
	else if (date1.m_year == date2.m_year && date1.m_month == date2.m_month && date1.m_day == date2.m_day)
		return false;
	else
		return true;
}
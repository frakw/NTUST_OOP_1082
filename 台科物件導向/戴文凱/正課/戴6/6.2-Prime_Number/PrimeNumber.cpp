/*
	int value;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();
	PrimeNumber operator++(int);
	PrimeNumber & operator--();
	PrimeNumber operator--(int);
*/
#include "PrimeNumber.h"

bool check_prime(int x) {//判斷質數
	int i=0;
	for (i = x != 1 ? 2 : 1; x % i;i++);
	return x == i && i > 1;
}

PrimeNumber::PrimeNumber() {
	value = 1;
}

PrimeNumber::PrimeNumber(int _value) {
	value = _value;
}

int PrimeNumber::get() {
	return value;
}

PrimeNumber& PrimeNumber::operator++() {//++在前面先++再傳值
	while (value++, !check_prime(value));
	return *this;
}

PrimeNumber& PrimeNumber::operator--() {//--在前面先--再傳值
	if (value < 3) {
		value = 1;
		return *this;
	}
	while (value--, !check_prime(value));
	return *this;
}

PrimeNumber PrimeNumber::operator++(int) {
	PrimeNumber temp;
	temp = *this;//++在後面先傳值再++，保留未加前的值
	while (value++, !check_prime(value));
	return temp;
}

PrimeNumber PrimeNumber::operator--(int) {
	PrimeNumber temp;
	temp = *this;//--在後面先傳值再--，保留未減前的值
	if (value < 3) {
		temp.value = 1;
		return temp;
	}
	while (value--, !check_prime(value));
	return temp;
}
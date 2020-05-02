#pragma once
class PrimeNumber {
public:
	int value=1;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();//++在前面
	PrimeNumber operator++(int);//++在後面，int一定要加，標記用
	PrimeNumber & operator--();//--在前面
	PrimeNumber operator--(int);//--在後面，int一定要加，標記用
};
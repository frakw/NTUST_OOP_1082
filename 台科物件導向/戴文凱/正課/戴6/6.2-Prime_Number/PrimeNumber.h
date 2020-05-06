#pragma once
class PrimeNumber {
public:
	int value=1;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();//++在前面，加完傳自己
	PrimeNumber operator++(int);//++在後面，int一定要加，標記用，加完傳未加之前的數值
	PrimeNumber & operator--();//--在前面，減完傳自己
	PrimeNumber operator--(int);//--在後面，int一定要加，標記用，減完傳未減之前的數值
};
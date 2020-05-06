#include "Polynomial.h"
#include <algorithm>
#include <cmath>
using namespace std;
Polynomial::Polynomial() {
	coefficient = new double(0.0);
}
Polynomial::~Polynomial() {
	delete[] coefficient;
	coefficient = nullptr;
}

Polynomial::Polynomial(const Polynomial& a) {//copy constructor 初始化時賦值一個相同型態的變數 ex: int a=87; int b=a;
	this->~Polynomial();
	size = a.size;
	coefficient = new double[size] {};//{}初始化全部為0
	for (int i = 0;i < a.size;i++) {
		coefficient[i] = a.coefficient[i];
	}
}
Polynomial::Polynomial(double* input, int in_size) {
	coefficient = new double[in_size];
	size = in_size;
	for (int i = 0;i < in_size;i++) {
		coefficient[i] = input[i];
	}
}


Polynomial Polynomial::operator+(const Polynomial& a) {
	Polynomial result;
	int min_size = size;
	int max_size = a.size;
	if (size > a.size) {
		swap(min_size, max_size);
	}
	result.size = max_size;
	result.coefficient = new double[result.size]{};//{}初始化全部為0
	for (int i = 0;i < min_size;i++) {//2個多項式共同有的項
		result.coefficient[i] = coefficient[i] + a.coefficient[i];
	}
	for (int i = min_size;i < max_size;i++) {//較多項的多項式，將剩餘係數存入result
		result.coefficient[i] = size > min_size ? coefficient[i] : a.coefficient[i];
	}
	result.clear_zero();
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& a) {
	Polynomial result;
	int min_size = size;
	int max_size = a.size;
	if (size > a.size) {
		swap(min_size, max_size);
	}
	result.size = max_size;
	result.coefficient = new double[result.size]{};//{}初始化全部為0
	for (int i = 0;i < min_size;i++) {//2個多項式共同有的項
		result.coefficient[i] = coefficient[i] - a.coefficient[i];
	}
	for (int i = min_size;i < max_size;i++) {//較多項的多項式，將剩餘係數存入result
		result.coefficient[i] = size > min_size ? coefficient[i] : (-1 * a.coefficient[i]);
	}
	result.clear_zero();
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& a) {
	Polynomial result;
	result.size = size + a.size - 1;
	result.coefficient = new double[result.size]{};//{}初始化全部為0
	for (int i = 0;i < size;i++) {
		for (int j = 0;j < a.size;j++) {
			result.coefficient[i + j] += coefficient[i] * a.coefficient[j];//ex:x^2 * x^3 = x^5 (i+j)
		}
	}
	result.clear_zero();
	return result;
}

double& Polynomial::operator[](int index) {//一定要return by reference，否則不能放等號左邊
	return coefficient[index];
}

double evaluate(const Polynomial& input, const double& a) {
	double result = 0;
	for (int i = 0;i < input.size;i++) {
		result += (input.coefficient[i] * pow(a, i));
	}
	return result;
}

Polynomial& Polynomial::operator=(const Polynomial& a) {
	this->~Polynomial();
	size = a.size;
	coefficient = new double[size] {};//{}初始化全部為0
	for (int i = 0;i < a.size;i++) {
		coefficient[i] = a.coefficient[i];
	}
	return *this;
}

Polynomial Polynomial::operator+(const double& a) {
	Polynomial result = *this;
	result[0] = coefficient[0] + a;
	result.clear_zero();
	return result;
}
Polynomial Polynomial::operator-(const double& a) {
	Polynomial result = *this;
	result[0] = coefficient[0] - a;
	result.clear_zero();
	return result;
}
Polynomial Polynomial::operator*(const double& a) {
	Polynomial result;
	result.size = size;
	result.coefficient = new double[result.size]{};//{}初始化全部為0
	for (int i = 0;i < size;i++) {
		result.coefficient[i] = coefficient[i] * a;
	}
	result.clear_zero();
	return result;
}

Polynomial operator+(const double& a,Polynomial& b) {
	Polynomial result = b;
	result = b + a;//呼叫上方的 Polynomial Polynomial::operator+(const double& a); 不用再實作
	return result;
}
Polynomial operator-(const double& a,Polynomial& b) {//常數-多項式，多項式內部係數會變負的
	Polynomial result ;
	result = (b * -1.0f);//呼叫上方的 Polynomial Polynomial::operator*(const double& a); 讓所有係數變負的
	result =  result + a;//呼叫上方的 Polynomial Polynomial::operator+(const double& a); 不用再實作
	return result;
}
Polynomial operator*(const double& a, const Polynomial& b) {
	Polynomial result;
	result.size = b.size;
	result.coefficient = new double[result.size]{};//{}初始化全部為0
	for (int i = 0;i < b.size;i++) {
		result.coefficient[i] = b.coefficient[i] * a;
	}
	result.clear_zero();
	return result;
}
#include <iostream>

using namespace std;

class Complex
{
public:
	double realValue, imaginaryValue;

	Complex();
	//~Complex();
	Complex(double r);
	//~Complex(double r);
	Complex(double r, double i);
	//~Complex(double r, double i);
	double real();
	double imag();
	double norm();
	friend double real(Complex c);
	friend double imag(Complex c);
	friend double norm(Complex c);	
	Complex operator+(Complex c);
	Complex operator-(Complex c);
	Complex operator*(Complex c);
	Complex operator/(Complex c);
	friend Complex operator+(double d, Complex c);
	friend Complex operator-(double d, Complex c);
	friend Complex operator*(double d, Complex c);
	friend Complex operator/(double d, Complex c);
	friend bool operator==(Complex c1, Complex c2);	
	friend ostream& operator<<(ostream &strm, const Complex &c);
	friend istream& operator>>(istream &strm,Complex &c);
};

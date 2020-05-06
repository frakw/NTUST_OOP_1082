/*
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
*/
#include "Complex.h"

Complex::Complex() {
	realValue = 0;
	imaginaryValue = 0;
}
Complex::Complex(double r) {
	realValue = r;
	imaginaryValue = 0;
}
Complex::Complex(double r,double i) {
	realValue = r;
	imaginaryValue = i;
}

double Complex::real() {
	return realValue;
}

double Complex::imag() {
	return imaginaryValue;
}

double Complex::norm() {
	return sqrt(pow(realValue, 2.0)+pow(imaginaryValue,2.0));
}

double real(Complex c) {
	return c.realValue;
}

double imag(Complex c) {
	return c.imaginaryValue;
}

double norm(Complex c) {
	return sqrt(pow(c.realValue, 2.0) + pow(c.imaginaryValue, 2.0));
}

Complex Complex::operator+(Complex c) {
	Complex temp;
	temp.realValue = realValue + c.realValue;
	temp.imaginaryValue = imaginaryValue + c.imaginaryValue;
	return temp;
}

Complex Complex::operator-(Complex c) {
	Complex temp;
	temp.realValue = realValue - c.realValue;
	temp.imaginaryValue = imaginaryValue - c.imaginaryValue;
	return temp;
}
	
Complex Complex::operator*(Complex c) {
	Complex temp;
	temp.realValue = (realValue * c.realValue - imaginaryValue*c.imaginaryValue);
	temp.imaginaryValue = (imaginaryValue*c.realValue+realValue*c.imaginaryValue);
	return temp;
}

Complex Complex::operator/(Complex c) {
	Complex temp;
	temp.realValue = (realValue * c.realValue + imaginaryValue * c.imaginaryValue)/(pow(c.realValue,2.0)+ pow(c.imaginaryValue, 2.0));
	temp.imaginaryValue = (imaginaryValue * c.realValue - realValue * c.imaginaryValue) / (pow(c.realValue, 2.0) + pow(c.imaginaryValue, 2.0));
	return temp;
}
//---------------------------------------------------------------------------------------------------
Complex operator+(double d,Complex c) {
	Complex temp;
	temp.realValue = d + c.realValue;
	temp.imaginaryValue = c.imaginaryValue;
	return temp;
}

Complex operator-(double d, Complex c) {
	Complex temp;
	temp.realValue = d - c.realValue;
	temp.imaginaryValue =  c.imaginaryValue;
	return temp;
}

Complex operator*(double d, Complex c) {
	Complex temp;
	temp.realValue = (d * c.realValue);
	temp.imaginaryValue = ( d * c.imaginaryValue);
	return temp;
}

Complex operator/(double d, Complex c) {
	Complex temp;
	temp.realValue = (d * c.realValue ) / (pow(c.realValue, 2.0) + pow(c.imaginaryValue, 2.0));
	temp.imaginaryValue = (-1 * d * c.imaginaryValue) / (pow(c.realValue, 2.0) + pow(c.imaginaryValue, 2.0));
	return temp;
}

bool operator==(Complex c1, Complex c2) {
	return (c1.realValue == c2.realValue) && (c1.imaginaryValue == c2.imaginaryValue);
}

ostream& operator<<(ostream& strm, const Complex& c) {
	strm << c.realValue << " + " << c.imaginaryValue << "*i"<<endl;
	return strm;
}

istream& operator>>(istream& strm, Complex& c) {
	string input;
	strm >> input;
	for (int i = 0;i < input.length();i++) {
		if (!isdigit(input[i])) {
			input[i] = ' ';//把非數字替換成空白，讓cin>>可以讀數字
		}
	}
	istringstream iss(input);
	iss >> c.realValue;
	iss >> c.imaginaryValue;
	return strm;
}

Complex::~Complex() {

}
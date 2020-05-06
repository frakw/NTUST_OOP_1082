#ifndef Fraction_H
#define Fraction_H
#include <iostream>
#include <iomanip>
using namespace std;

class Fraction {
public:
	void setNumerator(int);
	void setDenominator(int);
	void getDouble();
	void outputReducedFraction();
private:
	int Numerator;
	int Denominator;
};

#endif //Fraction_H
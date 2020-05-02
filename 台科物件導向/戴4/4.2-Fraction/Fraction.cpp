#include <iostream>
#include <cstdio>
#include "Fraction.h"
#define DBL_MAT_BITS 52
#define DBL_SIGN_MASK 0x8000000000000000ULL
#define DBL_EXP_MASK 0x7ff0000000000000ULL
#define DBL_MAT_MASK 0x000fffffffffffffULL
#define DBL_BASE_VALUE 1023
static int hcf(int, int);
static int is_int(double);
void Fraction::setNumerator(int a) {
	Numerator = a;
}
void Fraction::setDenominator(int a) {
	Denominator = a;
}
void Fraction::getDouble() {
	double temp = (double)Numerator / (double)Denominator;
	if (!is_int(temp)) {
		printf("%.6f\n", temp);
	}
	else {
		printf("%d\n", (int)temp);
	}
}
void Fraction::outputReducedFraction() {
	int x = hcf(Numerator, Denominator);
	std::cout << Numerator / x;
	if (Denominator / x != 1) {
		std::cout << "/" << (Denominator / x);
	}
	std::cout << std::endl;
}

static int hcf(int a, int b) {
	if (b) {
		return hcf(b, a % b);
	}
	else {
		return a;
	}
}


static int is_int(double x)
{
	unsigned long long v = *(unsigned long long*) & x;
	unsigned long long mat = (v & DBL_MAT_MASK);
	int exp = (int)((v & DBL_EXP_MASK) >> (DBL_MAT_BITS)) - DBL_BASE_VALUE;

	if (v == DBL_SIGN_MASK || v == 0ULL) return 1;
	if (exp < 0) return 0;
	mat <<= (DBL_MAT_BITS + exp);
	return mat == 0ULL;
}



#include "Circle.h"

Circle::Circle()
{
	r = 0;
}

void Circle::inputCircle()
{
	cin >> r;
}

double Circle::getArea()
{
	return PI * r * r;
}
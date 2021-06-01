#include "Cylinder.h"

Cylinder::Cylinder()
{
	width = 0;
}

void Cylinder::inputCylinder()
{
	circle.inputCircle();
	cin >> width;
}

double Cylinder::getVolume()
{
	return circle.getArea() * width;
}
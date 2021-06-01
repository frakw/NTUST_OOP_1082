#include "Car.h"

Car::Car()
{
	length = 0;
	width = 0;
	height = 0;
	wheelN = 0;
}

void Car::inputCar()
{
	cin >> length;
	cin >> width;
	cin >> height;
	cin >> wheelN;
	wheel.inputWheel();
}

double Car::getVolume()
{
	return (length * width * height) + (wheel.getVolume() * wheelN);
}

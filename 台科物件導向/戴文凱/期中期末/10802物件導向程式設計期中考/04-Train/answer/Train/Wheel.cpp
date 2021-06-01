#include "Wheel.h"

Wheel::Wheel()
{

}

void Wheel::inputWheel()
{
	tire.inputCylinder();
	axle.inputCylinder();
}

double Wheel::getVolume()
{
	return tire.getVolume() * 2 + axle.getVolume();
}
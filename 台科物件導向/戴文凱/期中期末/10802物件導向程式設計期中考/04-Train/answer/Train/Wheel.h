#ifndef Wheel_H 
#define Wheel_H

#include "Cylinder.h"

class Wheel : public Cylinder
{
private:
	Cylinder tire; 
	Cylinder axle; 

public:
	Wheel();
	void inputWheel();
	double getVolume();
};

#endif // Wheel_H 
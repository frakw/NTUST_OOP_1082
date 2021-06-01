#ifndef Car_H 
#define Car_H 
#include "Wheel.h"

class Car
{
private:
	double length;
	double width;
	double height;
	int wheelN;
	Wheel wheel;

public:
	Car();
	void inputCar();
	double getVolume();
};

#endif // Car_H 
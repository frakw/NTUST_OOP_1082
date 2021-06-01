#ifndef Cylinder_H 
#define Cylinder_H

#include "Circle.h"

class Cylinder : public Circle
{
private:
	double width;
	Circle circle;

public:
	Cylinder();
	void inputCylinder();
	double getVolume();
};

#endif // Cylinder_H 
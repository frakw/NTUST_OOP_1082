#ifndef Circle_H 
#define Circle_H

#include <iostream>
using namespace std;
const double PI = 3.14159;

class Circle
{
private:
	double r;
public:
	Circle();
	void inputCircle();
	double getArea();
};

#endif // Circle_H 
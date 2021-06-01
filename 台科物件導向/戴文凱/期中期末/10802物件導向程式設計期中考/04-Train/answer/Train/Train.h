#ifndef Train_H 
#define Train_H 
#include "Car.h"
#include <math.h>

class Train
{
private:
	Car car;
	int carN;
public:
	Train();
	void inputTrain();
	double getVolume();
	void printTrain();
};

#endif // Train_H 
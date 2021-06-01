#include "Train.h"

Train::Train()
{
}

void Train::inputTrain()
{
	cin >> carN;
	car.inputCar();
}

double Train::getVolume()
{
	return car.getVolume() * carN;
}

void Train::printTrain()
{
	int v = floor(getVolume());
	cout << v << endl;
}
#include "HotDogStand.h"
#include <iostream>

int HotDogStand::totalSellAmount;
HotDogStand::HotDogStand()
{
	hotDogSellAmount = 0;
}

HotDogStand::HotDogStand(string id)
{
	hotDogSellAmount = 0;
	standId = id;
}

HotDogStand::HotDogStand(string id, int amount)
{
	standId = id;
	hotDogSellAmount = amount;
	totalSellAmount += amount;
}


HotDogStand::~HotDogStand()
{

}

void HotDogStand::justSold()
{
	hotDogSellAmount++;
	totalSellAmount++;
}

void HotDogStand::print()
{
	std::cout << standId << " " << hotDogSellAmount << endl;
}

int HotDogStand::thisStandSoldAmount()
{
	return hotDogSellAmount;
}

int HotDogStand::allStandSoldAmount()
{
	return totalSellAmount;
}
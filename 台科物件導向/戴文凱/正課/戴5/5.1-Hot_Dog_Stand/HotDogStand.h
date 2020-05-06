#ifndef _HOTDOG
#define _HOTDOG
#include<string>
using namespace std;
class HotDogStand
{
public:
	HotDogStand();
	HotDogStand(string id);
	HotDogStand(string id, int amount);
	~HotDogStand();
	void justSold();
	void print();
	int thisStandSoldAmount();
	static int allStandSoldAmount();
private:
	string standId;
	int hotDogSellAmount;
	static int totalSellAmount;
};
#endif

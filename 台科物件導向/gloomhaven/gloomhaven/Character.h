#pragma once
#include <string>
using namespace std;
class Creature;
class Character : public Creature {
public:
	Character();
	Character(string in_name, int val, int in_card_amount);
	Character& operator=(const Character& input);
};
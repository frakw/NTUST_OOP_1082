#pragma once
using namespace std;
class Creature;
class Character : public Creature {
public:
	Character();
	Character(string in_name, int val, int in_card_amount);
	Character& operator=(const Character& input);
	bool choose_card();//選擇2張卡或長休或check，bool回傳是否選擇成功
	void print();//排序後的列印
	void action();//行動
	//Card use_card[2];//該輪選擇的2張卡，已轉移至basic
	bool sleep = false;//是否長休
};
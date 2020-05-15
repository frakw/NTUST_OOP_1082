#pragma once
using namespace std;
class Skill {
public:
	Skill();
	Skill(string name, int val);
	Skill(int in_type, int val);
	void set(string name, int val);
	int type=-1;
	int value=-1;
	int range = -1;//attack時才用到
	string move_step;//只在怪物卡技能為move時使用，存wasd
};

class Card {//copy constructor
public:
	Card();
	Card(const Card& input);
	Card(int in_agility, bool mark, Skill* a);
	Card(int in_agility, bool mark, Skill* a, Skill* b);
	~Card();
	Card& operator=(const Card& input);
	bool available=true;//此卡是否還可被使用
	bool discard = false;//是(true)否(false)在棄牌堆
	Skill* skill_up = nullptr;
	int skill_up_amount = 0;
	Skill* skill_down = nullptr;//怪物卡沒下半部，nullptr
	int skill_down_amount = 0;
	int number=0;//編號
	int agility=0;//敏捷值
	bool rewash_mark = false;//重洗標記，角色沒有重洗標記(false)
};


class Creature {
public:
	Creature();
	Creature(string in_name, int val, int in_card_amount);
	~Creature();
	Card* card = nullptr;//選擇卡牌
	string name="";
	int life_value=0;
	int card_amount=0;//可選卡牌數量
	int card_total =0;//總卡牌數量
	char code=0;//代號
	Coord position = {-1,-1};

};



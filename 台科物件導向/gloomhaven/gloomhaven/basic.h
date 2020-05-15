#pragma once
#include <string>
#include "Map.h"
using namespace std;
class Skill {
public:
	Skill():type(-1), value(-1){}
	Skill(string name, int val) : value(val) {
		this->set(name, val);
	}
	Skill(int type, int val) : value(val) {
		if (type < 0 || type > 3) {
			type = -1;//skill type error!
		}
		else {
			type = type;
		}
	}
	void set(string name, int val) {
		if (name == "move") {
			type = 0;
		}
		else if (name == "attack") {
			type = 1;
		}
		else if (name == "heal") {
			type = 2;
		}
		else if (name == "shield") {
			type = 3;
		}
		else {
			type = -1;//skill type error!
		}
		value = val;
	}
	int type=-1;
	int value=-1;
	int range = -1;//attack時才用到
	string move_step;//只在怪物卡技能為move時使用，存wasd
};

class Card {//copy constructor
public:
	Card() {};
	Card(const Card& input) {
		*this = input;
	};
	Card(int in_agility, bool mark, Skill* a) : agility(in_agility), rewash_mark(mark), skill_up(a) {}
	Card(int in_agility,bool mark, Skill* a,Skill* b) : agility(in_agility), rewash_mark(mark), skill_up(a), skill_down(b){}
	~Card() {
		if (skill_up != nullptr) {
			delete[] skill_up;
			skill_up = nullptr;
			skill_up_amount = 0;
		}
		if (skill_down != nullptr) {
			delete[] skill_down;
			skill_down = nullptr;
			skill_down_amount = 0;
		}
	}
	Card& operator=(const Card& input) {
		this->~Card();
		if (input.skill_up_amount > 0) {
			this->skill_up_amount = input.skill_up_amount;
			skill_up = new Skill[skill_up_amount];
			for (int i = 0;i < skill_up_amount;i++) {
				skill_up[i] = input.skill_up[i];
			}
		}
		if (input.skill_down_amount > 0) {
			this->skill_down_amount = input.skill_down_amount;
			skill_down = new Skill[skill_down_amount];
			for (int i = 0;i < skill_down_amount;i++) {
				skill_down[i] = input.skill_down[i];
			}
		}
		discard = input.discard;
		number = input.number;
		agility = input.agility;
		rewash_mark = input.rewash_mark;
		return *this;
	}
	bool available=true;//此卡是否還可被使用
	bool discard = false;//是(true)否(false)在棄牌堆
	Skill* skill_up = nullptr;
	int skill_up_amount = 0;
	Skill* skill_down = nullptr;//怪物卡沒下半部，nullptr
	int skill_down_amount = 0;
	int number;//編號
	int agility=0;//敏捷值
	bool rewash_mark = false;//重洗標記，角色沒有重洗標記(false)
};


class Creature {
public:
	Creature() {}
	Creature(string in_name, int val, int in_card_amount) :name(in_name), life_value(val), card_amount(in_card_amount) {
	
	}
	~Creature() {
		if (card != nullptr) delete[] card;
	}
	Card* card = nullptr;//選擇卡牌
	string name="";
	int life_value=0;
	int card_amount=0;//可選卡牌數量
	int card_total =0;//總卡牌數量
	char code=0;//代號
	Coord position = {-1,-1};

};



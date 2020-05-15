#include "Coord.h"
#include <string>
#include "basic.h"
Skill::Skill():type(-1), value(-1) {
	
}

Skill::Skill(string name, int val) : value(val) {
	this->set(name, val);
}

Skill::Skill(int in_type, int val) : value(val) {
	if (in_type < 0 || in_type > 3) {
		this->type = -1;//skill type error!
	}
	else {
		this->type = in_type;
	}
}
void Skill::set(string name, int val) {
	if (name == "move") {
		this->type = 0;
	}
	else if (name == "attack") {
		this->type = 1;
	}
	else if (name == "heal") {
		this->type = 2;
	}
	else if (name == "shield") {
		this->type = 3;
	}
	else {
		this->type = -1;//skill type error!
	}
	this->value = val;
}

//============================================================
Card::Card() {

}
Card::Card(const Card& input) {
	*this = input;
}
Card::Card(int in_agility, bool mark, Skill* a) : agility(in_agility), rewash_mark(mark), skill_up(a) {}
Card::Card(int in_agility, bool mark, Skill* a, Skill* b) : agility(in_agility), rewash_mark(mark), skill_up(a), skill_down(b) {}
Card::~Card() {
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
Card& Card::operator=(const Card& input) {
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

//==================================================================
Creature::Creature() {}
Creature::Creature(string in_name, int val, int in_card_amount) :name(in_name), life_value(val), card_amount(in_card_amount) {

}
Creature::~Creature() {
	if (card != nullptr) delete[] card;
}
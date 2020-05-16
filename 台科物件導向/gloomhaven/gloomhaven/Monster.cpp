#include "Gloom_Haven.h"
Monster::Monster() :Creature() {
}
Monster::Monster(string in_name, int val, int in_damage, int in_range, bool in_elite) : Creature(in_name, val, 6), damage(in_damage), range(in_range), elite(in_elite) {
}
Monster& Monster::operator=(const Monster& input) {
	this->name = input.name;
	this->damage = input.damage;
	this->range = input.range;
	this->life_value = input.life_value;
	this->max_life_value = input.max_life_value;
	this->card_amount = input.card_amount;
	this->card_total = input.card_total;
	this->code = input.code;
	this->position = input.position;
	//this->TmpShield = input.TmpShield;
	this->TmpAgility = input.TmpAgility;
	this->team_num = input.team_num;


	//elite¨t¦C---------------------------------
	this->elite = input.elite;
	this->elite_max_life_value = input.elite_max_life_value;
	this->elite_damage = input.elite_damage;
	this->elite_range = input.elite_range;
	//------------------------------------------
	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		card[i] = input.card[i];
	}
	return *this;
}
void Monster::switch_status(int num) {
	switch (num)
	{
	case 0:show = false;break;
	case 1:break;
	case 2: {
		elite = true;
		damage = elite_damage;
		max_life_value = elite_max_life_value;
		life_value = elite_max_life_value;
		range = elite_range;
	}break;
	default:break;
	}
}

void Monster::choose_card(bool debug_mode) {
	if (debug_mode) {
		use_card = card[debug_mode_card_number];
		debug_mode_card_number++;
	}
	else {
		use_card = card[rand() % card_amount];
	}
	TmpAgility = use_card.agility;
}


void Monster::move() {
	cout << "monster move" << endl;
}
void Monster::attack() {
	cout << "monster attack" << endl;
}
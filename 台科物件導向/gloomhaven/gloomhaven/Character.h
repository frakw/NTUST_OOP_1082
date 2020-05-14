#pragma once
#include "basic.h"
class Character : public Creature {
public:
	Character() :Creature(){}
	Character(string in_name, int val, int in_card_amount) :Creature(in_name, val, in_card_amount) {
	}
	Character& operator=(const Character& input) {
		this->name = input.name;
		this->life_value = input.life_value;
		this->card_amount = input.card_amount;
		this->card_total = input.card_total;
		this->code = input.code;
		this->card = new Card[card_amount];
		for (int i = 0;i < card_amount;i++) {
			this->card[i] = input.card[i];
		}
		return *this;
	}
};
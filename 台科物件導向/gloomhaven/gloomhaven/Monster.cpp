#include "Gloom_Haven.h"
Monster::Monster() :Creature() {

}
Monster::Monster(string in_name, int val, int in_damage, int in_range, bool in_elite) : Creature(in_name, val, 6), damage(in_damage), range(in_range), elite(in_elite) {
}
Monster& Monster::operator=(const Monster& input) {
	name = input.name;
	life_value = input.life_value;
	max_life_value = input.max_life_value;
	card_amount = input.card_amount;
	card_total = input.card_total;
	code = input.code;
	position = input.position;
	card = new Card[card_amount];
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
		life_value = elite_life_value;
		range = elite_range;
	}break;
	default:break;
	}
}
#include "Gloom_Haven.h"

using namespace std;

Gloom_Haven::Gloom_Haven(tuple<Character*, int, Monster*, int, Map*>input, bool mode) :DEBUG_MODE(mode) {
	this->seiting(input, mode);
}
void Gloom_Haven::seiting(tuple<Character*, int, Monster*, int, Map*> input, bool mode) {
	DEBUG_MODE = mode;
	map = get<4>(input);

	this->character = get<0>(input);
	map->character = get<0>(input);

	this->character_amount = get<1>(input);
	map->character_amount = get<1>(input);
	//this->character_remain = this->character_amount;

	this->monster = get<2>(input);
	map->monster = get<2>(input);

	this->monster_amount = get<3>(input);
	map->monster_amount = get<3>(input);
	//this->monster_remain = this->character_amount;

	all = new Creature * [character_amount + monster_amount];//所有角色與怪物存放區(方便敏捷值排序用)，先角色再怪物
	for (int i = 0;i < character_amount;i++) {
		all[i] = character + i;
	}
	for (int i = 0;i < monster_amount;i++) {
		all[i+ character_amount] = monster + i;
	}
}

void Gloom_Haven::start() {
	cout << "game start"<< endl;

	this->map->change_char();
	this->map->check_room();
	this->map->show_room();
	for (int i = 0;i < character_amount;i++) {
		string step;
		cin >> step;
		this->map->choose_pos(i,step);
		this->map->show_room();
	}
	int round_count = 1;
	char code;
	while (character_remain() != 0 && monster_remain() != 0) {
		int card_number1, card_number2;
		cout << "round " << round_count << endl;
		for (int i = 0;i < character_amount;i++) {
			if (character[i].card_hand_amount() < 2 && character[i].card_throw_amount() < 2) {//檢查有無角色無法長休或出牌，死亡
				character[i].life_value = 0;
				this->map->show_room();
			}
		}
		for (int i = 0;i < character_amount;i++) {//角色選牌
			cin >> code;
			if (character[i].code == code) {
				while (!character[i].choose_card());
			}
		}
		for (int i = 0;i < monster_amount;i++) {//怪物選牌
			monster[i].choose_card(DEBUG_MODE);
		}

		round_count++;
	}
	if (!character_remain()) {
		cout << "monster win~" << endl;
	}
	else {
		cout << "character win~" << endl;
	}
}

void Gloom_Haven::stop() {
	
}
Gloom_Haven::Gloom_Haven() {

}

Gloom_Haven::Gloom_Haven(bool mode) :DEBUG_MODE(mode) {

}
Gloom_Haven::~Gloom_Haven() {
	//if (map != nullptr) { map 要在class txt 裡釋放記憶體(因為地圖會重新載入)，否則會重複釋放記憶體
	//	delete map;//不可用delete[]
	//	map = nullptr;
	//}
	if (character != nullptr) {
		delete[] character;
	}
	if (monster != nullptr) {
		delete[] monster;
	}
	if (all != nullptr) {
		delete[] all;
	}
}

int Gloom_Haven::character_remain() {//角色剩餘數
	int count = 0;
	for (int i = 0;i < character_amount;i++) {
		if (character[i].life_value > 0) {
			count++;
		}
	}
	return count;
}
int Gloom_Haven::monster_remain() {//怪物剩餘數
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0) {
			count++;
		}
	}
	return count;
}
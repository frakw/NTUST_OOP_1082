#define DEBUG
#include "Gloom_Haven.h"
#undef DEBUG
using namespace std;


Gloom_Haven::Gloom_Haven(tuple<Character*, int, Monster*, int, Map*>input){
	this->set(input);
}

void Gloom_Haven::set(tuple<Character*, int, Monster*, int, Map*> input) {
	this->map = get<4>(input);

	this->character = get<0>(input);
	this->map->character = get<0>(input);

	this->character_amount = get<1>(input);
	this->map->character_amount = get<1>(input);

	this->monster = get<2>(input);
	this->map->monster = get<2>(input);

	this->monster_amount = get<3>(input);
	this->map->monster_amount = get<3>(input);

	this->all = new Creature * [this->character_amount + this->monster_amount];//所有角色與怪物排序後存放區，先角色再怪物
	for (int i = 0;i < this->character_amount;i++) {
		this->all[i] = this->character + i;
	}
	for (int i = 0;i < this->monster_amount;i++) {
		this->all[i+ this->character_amount] = this->monster + i;
		this->add_to_group(this->monster + i);
	}
}

void Gloom_Haven::start() {
	this->map->check_room();
	this->map->set_choosing_environment();//選擇位置時專用，choose_pos裡也會呼叫到
	for (int i = 0;i < character_amount;i++) {
		prompt_input("請選擇角色 "<<character[i].code<<" 的位置:");
		this->map->show_choosing_room();//輸出選擇時的地圖，輸出前要set_choosing_environment
		this->map->choose_pos(i,wasd());//選擇位置主程式
	}
	prompt_input("起始地圖:");
	this->map->show_room();//第一次輸出地圖(非選擇狀態)
	prompt_input("開始遊戲");
	int round_count = 1;
	string choose;
	while (1){
		if (monster_remain() == 0 && map->door_amount() == 0) {
			cout << "character win~" << endl;
			break;
		}
		else if (character_remain() == 0) {
			cout << "monster win~" << endl;
			break;
		}
		cout << "round " << round_count <<':'<< endl;
		for (int i = 0;i < character_amount;i++) {//檢查有無角色無法長休或出牌
			if (character[i].card_hand_amount() < 2 && character[i].card_discard_amount() < 2 && character[i].life_value > 0/*該角色也必須存活*/) {
				character[i].life_value = 0;
				cout << character[i].code << " is killed!!" << endl;
				this->map->show_room();
			}
		}
		while(choose_remain()) {//角色選牌(這個不能用virtual，因為會check並且順序不一定)
			choose = character_card_choose();
			int i;
			for (i = 0;i < character_amount;i++) {
				if (character[i].code == choose[0] && character[i].life_value > 0) {
					character[i].choose_card(choose.substr(2));
					break;
				}
			}
			if (i == character_amount) {
				cout << "character not found,please input again!" << endl;
			}
		}
		for (int i = 0;i < all_group.size();i++) {
			if (!monster_race_amount(all_group[i].name)) continue;
			if (!debug_mode) {
				do {
					all_group[i].card_number = rand() % all_group[i].member[i]->card_amount;
				} while (monster_race_in_discard(all_group[i].name, all_group[i].card_number));
			}
			else {
				all_group[i].card_number++;
			}
			all_group[i].choose_card();
		}
		sort(all, all + character_amount + monster_amount, creature_order_compare);
		prompt_input("角色與怪物行動順序如下:");
		for (int i = 0;i < character_amount + monster_amount;i++) {//印出順序 角色印敏捷值與手牌編號 怪物印卡牌內容
			all[i]->print();//virtual
		}
		prompt_input("行動階段:");
		for (int i = 0;i < character_amount + monster_amount;i++) {//行動時間
			all[i]->action();//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//該回合結束後的重整(重設數值)
			all[i]->round_end();//virtual
		}


		if (this->map->check_room()) {//重新檢查房間視野，並將開啟的門設為地板，有開門就重新輸出地圖
			this->map->show_room();//有開門才需要輸出地圖
		}
		
		for (int i = 0;i < all_group.size();i++) {
			if (!monster_race_amount(all_group[i].name)) continue;
			all_group[i].round_end();
		}
		round_count++;
	}
}

Gloom_Haven::Gloom_Haven() {}

Gloom_Haven::~Gloom_Haven() {
	//if (map != nullptr) { map 要在class txt 裡釋放記憶體(因為地圖會重新載入)，否則會重複釋放記憶體
	//	delete map;//不可用delete[]
	//	map = nullptr;
	//}
	mydelete(character);
	mydelete(monster);
	mydelete(all);
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
		if (monster[i].life_value > 0 && monster[i].show) {
			count++;
		}
	}
	return count;
}

int Gloom_Haven::choose_remain() {//剩餘幾個角色未選牌或長休
	int count = 0;
	for (int i = 0;i < character_amount;i++) {
		if (!character[i].finished_choose && character[i].life_value > 0) {//未選牌且活著
			count++;
		}
	}
	return count;
}

bool creature_order_compare(const Creature* const& a,const Creature* const& b) {
	if (a->use_card[0].agility == b->use_card[0].agility) {
		if (a->team_num == b->team_num) {//隊伍與敏捷相同
			if (a->team_num == Team_num::character) {//角色與角色敏捷相同
				if (a->use_card[1].agility == b->use_card[1].agility) {
					return a->code < b->code;
				}
				return a->use_card[1].agility < b->use_card[1].agility;
			}
			else if (a->team_num == Team_num::monster) {//怪物與怪物敏捷相同
				return a->code < b->code;
			}
		}
		else {//角色與怪物敏捷相同
			return a->team_num == Team_num::character;
		}
	}
	return a->use_card[0].agility < b->use_card[0].agility;
}

int Gloom_Haven::monster_race_amount(string name) {
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].name == name && monster[i].show_in_room && monster[i].show && monster[i].life_value > 0) {
			count++;
		}
	}
	return count;
}

bool Gloom_Haven::monster_race_in_discard(string name, int card_num) {
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].name == name && monster[i].show_in_room && monster[i].show && monster[i].life_value > 0) {
			return monster[i].in_discard(card_num);
		}
	}
	return false;
}


void Gloom_Haven::add_to_group(Monster* add) {
	for (int i = 0;i < all_group.size();i++) {
		if (all_group[i].name == add->name) {
			all_group[i].member.push_back(add);
			return;
		}
	}
	Race new_group;
	new_group.name = add->name;
	all_group.push_back(new_group);
	all_group.back().member.push_back(add);
}

void Race::choose_card() {
	for (int i = 0;i < member.size();i++) {
		member[i]->use_card[0] = member[i]->find_card(card_number);
		member[i]->find_card(card_number).discard = true;
	}
}

void Race::round_end() {
	if (member[0]->find_card(card_number).rewash_mark) {
		for (int i = 0;i < member.size();i++) {
			member[i]->discard_to_hand();
			card_number = -1;
		}
	}
}
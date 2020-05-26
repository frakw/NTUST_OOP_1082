#include "Gloom_Haven.h"

using namespace std;

Gloom_Haven::Gloom_Haven(tuple<Character*, int, Monster*, int, Map*>input, bool mode) :DEBUG_MODE(mode) {
	this->set(input, mode);
}

void Gloom_Haven::set(tuple<Character*, int, Monster*, int, Map*> input, bool mode) {
	this->DEBUG_MODE = mode;
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
	}
}

void Gloom_Haven::start() {
	this->map->check_room();
	this->map->set_choosing_environment();//選擇位置時專用，choose_pos裡也會呼叫到
	for (int i = 0;i < character_amount;i++) {
		this->map->show_choosing_room();//輸出選擇時的地圖，輸出前要set_choosing_environment
		this->map->choose_pos(i,wasd());//選擇位置主程式
	}
	this->map->show_room();//第一次輸出地圖(非選擇狀態)
	int round_count = 1;
	string choose;
	while ((character_remain() != 0 && monster_remain() != 0) || this->map->door_amount()!=0) {
		cout << "round " << round_count <<':'<< endl;
		bool card_too_little = false;
		for (int i = 0;i < character_amount;i++) {//檢查有無角色無法長休或出牌
			if (character[i].card_hand_amount() < 2 && character[i].card_discard_amount() < 2 && character[i].life_value>0/*該角色也必須存活*/) {
				character[i].life_value = 0;
				card_too_little = true;
			}
		}
		if (card_too_little) {
			this->map->show_room();//有角色死亡後輸出最終地圖
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
		for (int i = 0;i < monster_amount;i++) {//怪物選牌
			monster[i].choose_card(DEBUG_MODE);
		}
		sort(all, all + character_amount + monster_amount,
			[](Creature* const& a, Creature* const& b) -> bool {
				if (a->use_card[0].agility == b->use_card[0].agility) {
					if (a->team_num == b->team_num) {//隊伍與敏捷相同
						if (a->team_num == 0) {//角色與角色敏捷相同
							if (a->use_card[1].agility == b->use_card[1].agility) {
								return a->code < b->code;
							}
							return a->use_card[1].agility < b->use_card[1].agility;
						}
						else if (a->team_num == 1) {//怪物與怪物敏捷相同
							return a->code < b->code;
						}
					}
					else {//角色與怪物敏捷相同
						return a->team_num == 0;
					}
				}
				return a->use_card[0].agility < b->use_card[0].agility;
			});

		for (int i = 0;i < character_amount + monster_amount;i++) {//印出順序 角色印敏捷值與手牌編號 怪物印卡牌內容
			all[i]->print();//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//行動時間
			all[i]->action(DEBUG_MODE);//virtual
		}
		for (int i = 0;i < character_amount + monster_amount;i++) {//該回合結束後的重整(重設數值)
			all[i]->round_end(DEBUG_MODE);//virtual
		}

		if (this->map->check_room()) {//重新檢查房間視野，並將開啟的門設為地板，有開門就重新輸出地圖
			this->map->show_room();//有開門才需要輸出地圖
		}
		round_count++;
	}
	if (!monster_remain()) {
		cout << "character win~" << endl;
	}
	else {
		cout << "monster win~" << endl;
	}
}

Gloom_Haven::Gloom_Haven() {

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
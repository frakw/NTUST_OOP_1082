#include "Gloom_Haven.h"

Character::Character() :Creature() {
}
Character::Character(string in_name, int val, int in_card_amount) :Creature(in_name, val, in_card_amount) {
}
Character& Character::operator=(const Character& input) {
	this->name = input.name;
	this->life_value = input.life_value;
	this->max_life_value = input.max_life_value;
	this->card_amount = input.card_amount;
	this->card_total = input.card_total;
	this->code = input.code;
	this->position = input.position;
	this->use_card[0] = input.use_card[0];
	this->use_card[1] = input.use_card[1];
	this->sleep = input.sleep;
	this->TmpShield = input.TmpShield;
	this->team_num = input.team_num;
	this->map = input.map;
	this->finished_choose = input.finished_choose;

	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		this->card[i] = input.card[i];
	}
	return *this;
}

void Character::choose_card(string input) {
	if (life_value <= 0) {
		cout << "this character already died! input again!" << endl;
		return;
	}

	stringstream ss(input);
	string card_number1;//因有可能輸入check，顧使用string
	int  card_number2;
	ss >> card_number1;
	if (card_number1 == "check") {
		//資訊
		this->check_card();
		return;
	}
	if (finished_choose) {//曾經輸入過
		cout << "this character already choose card,Do you want to modify it(y/n)?" << endl;
		char ch = getline_char();
		while (ch != 'y' && ch != 'n') {
			cout << err << endl;
			ch = getline_char();
		}
		if (ch == 'n') {
			return;
		}
		sleep = false;//remember
	}
	if (card_number1 == "-1") {
		//長休
		sleep = true;
		use_card[0].agility = 99;
		use_card[1].agility = 99;
		finished_choose = true;
	}
	else {
		ss >> card_number2;
		if (card_in_hand(atoi(card_number1.c_str())) && card_in_hand(card_number2)) {
			use_card[0] = find_card(atoi(card_number1.c_str()));
			use_card[1] = find_card(card_number2);
			finished_choose = true;
		}
		else {
			cout << "card number is not correct(not exist or discard or unavailable)! please input again!"<<endl;
		}
	}
}

void Character::print(){
	if (life_value > 0) {//角色不判斷是否出現
		cout << code << ' ' << use_card[0].agility << ' ';
		if (!sleep) {
			cout << use_card[0].number << ' ' << use_card[1].number;
		}
		else {
			cout << "-1";
		} 
		cout << endl;
	}
}

void Character::action(bool) {
	if (life_value <= 0) {
		return;
	}
	cout << code << "'s turn: card ";
	if (sleep) {//長休，   ====== 尚未檢查IO err
		cout << "-1" << endl;
		this->heal(2);
#ifdef prompt_input
		cout << "請輸入要移除卡牌:" << endl;
#endif
		int remove_number = getline_int();
		while (!card_in_discard(remove_number)) {
			cout << "card number is not correct(not exist or in hand or unavailable)! please input again!" << endl;
			remove_number = getline_int();
		}
		find_card(remove_number).available = false;
		cout << "remove card: " << remove_number << endl;
		return;
	}
	else {
		cout << use_card[0].number << ' ' << use_card[1].number << endl;
	}
	bool card_first_index;
	string NumUD;
	int num;
num_err:
	NumUD = character_card_first_ud();
	while(NumUD == "check") {
		map->check();
		goto num_err;
	}
	num = atoi(NumUD.substr(0, NumUD.length() - 1).c_str());
	if (num != use_card[0].number && num != use_card[1].number) {
		cout << "card number error!,please choose one of the two selected cards" << endl;
		goto num_err;
	}
	card_first_index = (use_card[0].number == (NumUD[0] - '0'))?false:true;
	if (NumUD[1] == 'u') {//上半部
		for (int i = 0;i < use_card[card_first_index].skill_up_amount;i++) {//第一張
			run_skill(use_card[card_first_index].skill_up[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_down_amount;i++) {//第二張
			run_skill(use_card[!card_first_index].skill_down[i]);
		}
	}
	else {//下半部
		for (int i = 0;i < use_card[card_first_index].skill_down_amount;i++) {//第一張
			run_skill(use_card[card_first_index].skill_down[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_up_amount;i++) {//第二張
			run_skill(use_card[!card_first_index].skill_up[i]);
		}
	}
}

void Character::run_skill(Skill skill) {
	switch (skill.type) {
	case 0: {//move
		this->move(wasd(), skill.value);
	}break;
	case 1: {//attack
		this->attack(skill);
	}break;
	case 2: {//heal
		this->heal(skill.value);
	}break;
	case 3: {//shield
		this->shield(skill.value);
	}break;
	}
}

void Character::attack(Skill skill) {
	char mon_code;
	int index =-1;
	mon_code = getline_char();
	if (mon_code == '0') {
		return;
	}
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster[i].code == mon_code) {
			index = i;
			break;
		}
	}
	if (index == -1) {//bad index
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
	int tmprange = map->a_star_path_step(this, map->monster + index);
	if (tmprange <= skill.range/*檢查射程*/ &&
		tmprange!=-87 /*可以到達(無法到達回傳-87)*/ &&
		map->monster[index].show /*該怪物有出現*/ &&
		map->monster[index].life_value>0/*該怪物存活*/ &&
		map->in_vision(position, map->monster[index].position)){//視野之內(線性差值法)

		map->monster[index].be_attack(this->code,skill.value);
	}
	else {
		cout << "error target!!!" << endl;
		this->attack(skill);
		return;
	}
}

void Character::round_end(bool debug_mode) {//該回合結束後的重整(重設數值)
	if (!sleep) {//沒長休就將出的2張牌移至棄牌堆
		find_card(use_card[0].number).discard = true;
		find_card(use_card[1].number).discard = true;
	}
	else {//長休
		this->discard_to_hand();//棄牌堆所有牌移回手牌(不包含已移除的牌)
	}
	finished_choose = life_value <= 0;
	sleep = false;
	TmpShield = 0;

}
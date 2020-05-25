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
	//this->TmpAgility = input.TmpAgility;
	this->TmpShield = input.TmpShield;
	this->team_num = input.team_num;
	this->map = input.map;

	this->card = new Card[card_amount];
	for (int i = 0;i < card_amount;i++) {
		this->card[i] = input.card[i];
	}
	return *this;
}

bool Character::choose_card() {
	if (life_value < 0) {
		return true;
	}
	string card_number1;//因有可能輸入check，顧使用string
	int  card_number2;
	cin >> card_number1;
	if (card_number1 == "check") {
		//資訊
		this->check_card();
		return false;
	}
	else if (card_number1 == "-1") {
		//長休
		sleep = true;
		use_card[0].agility = 99;
		use_card[1].agility = 99;
//#ifdef prompt_input
//		cout << "請輸入要移除卡牌:" << endl;
//#endif
		//cin >> card_number2;//    行動階段再做
		//find_card(card_number2).available = false;//    行動階段再做
		//this->heal(2);//    行動階段再做
		//TmpAgility = 99;//    行動階段再做
		//this->discard_to_hand();//棄牌堆所有牌移回手牌 //    行動階段再做
	}
	else {
		cin >> card_number2;
		sleep = false;//要記得***
		use_card[0] = find_card(atoi(card_number1.c_str()));
		use_card[1] = find_card(card_number2);
		//err handle 若輸入在棄牌堆或以移除牌 not finished
		//TmpAgility = use_card[0].agility;//第一張牌作為敏捷值
	}
	return true;
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
	if (sleep) {//長休
		cout << "-1" << endl;
#ifdef prompt_input
		cout << "請輸入要移除卡牌:" << endl;
#endif
		int remove_card_number;
		cin >> remove_card_number;
		find_card(remove_card_number).available = false;
		this->heal(2);
		cout << "remove card: " << remove_card_number << endl;
		return;
	}
	else {
		cout << use_card[0].number << ' ' << use_card[1].number << endl;
	}
	bool card_first_index;
	string number_up_down;
	cin >> number_up_down;
	while(number_up_down == "check") {
		map->check();
		cin >> number_up_down;
	}
	card_first_index = (use_card[0].number == (number_up_down[0] - '0'))?false:true;
	if (number_up_down[1] == 'u') {//上半部
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
		string step;
		cin >> step;
		this->move(step, skill.value);
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
	char code;
	int index =-1;
	cin >> code;
	if (code == '0') {
		return;
	}
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster[i].code == code) {
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

		map->monster[index].be_attack(code,skill.value);
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
	sleep = false;
	TmpShield = 0;

}
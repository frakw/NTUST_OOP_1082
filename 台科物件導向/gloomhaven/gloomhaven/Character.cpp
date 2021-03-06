#include "Gloom_Haven.h"

Character::Character() :Creature() {
	this->team_num = Team_num::character;
}
Character::~Character(){
	mydelete(card);
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
	}
	if (card_number1 == "-1" && ss.eof()) {
		//長休
		if (card_discard_amount() < 1) {
			cout << err << endl;
			prompt_input("棄牌堆數量不足，無法長休");
			return;
		}
		sleep = true;
		use_card[0].agility = 99;
		use_card[1].agility = 99;
		finished_choose = true;
	}
	else {
		ss >> card_number2;
		if (in_hand(stoi(card_number1)) &&
			in_hand(card_number2) && /*檢查是否重複*/
			stoi(card_number1)!= card_number2) 
		{
			use_card[0] = find_card(stoi(card_number1));
			use_card[1] = find_card(card_number2);
			finished_choose = true;
			sleep = false;
		}
		else {
			cout << "card number is not correct(not exist or discard or duplication or unavailable)! please input again!"<<endl;
		}
	}
}

void Character::print() {//virtual
	if (life_value > 0) {//角色不判斷是否出現
		cout << code << ' ' << setw(2) << setfill('0') << use_card[0].agility << ' ';
		if (!sleep) {
			cout << use_card[0].number << ' ' << use_card[1].number;
		}
		else {
			cout << "-1";
		}
		cout << endl;
	}
};

void Character::action() {//virtual
	if (life_value <= 0) {
		return;
	}
	cout << code << "'s turn: card ";
	if (sleep) {//長休
		cout << "-1" << endl;
		this->heal(2);
		prompt_input("請從棄牌堆中輸入要移除卡牌編號:");
		int remove_number = getline_int();
		while (!in_discard(remove_number)) {
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
	while (NumUD == "check") {
		map->check();
		goto num_err;
	}
	num = stoi(NumUD.substr(0, NumUD.length() - 1));
	if (num != use_card[0].number &&
		num != use_card[1].number)
	{
		cout << "card number error!,please choose one of the two selected cards" << endl;
		goto num_err;
	}
	card_first_index = (use_card[0].number == (NumUD[0] - '0')) ? false : true;
	if (NumUD[1] == 'u') {//上半部
		for (int i = 0;i < use_card[card_first_index].skill_up_amount;i++) {//第一張
			run_skill(use_card[card_first_index].skill_up[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_down_amount;i++) {//第二張
			run_skill(use_card[!card_first_index].skill_down[i]);
		}
	}
	else if (NumUD[1] == 'd') {//下半部
		for (int i = 0;i < use_card[card_first_index].skill_down_amount;i++) {//第一張
			run_skill(use_card[card_first_index].skill_down[i]);
		}
		for (int i = 0;i < use_card[!card_first_index].skill_up_amount;i++) {//第二張
			run_skill(use_card[!card_first_index].skill_up[i]);
		}
	}
};

void Character::run_skill(const Skill const& skill) {
	switch (skill.type) {
	case skill_type::move: {//move
		this->move(wasd(), skill.value);
	}break;
	case skill_type::attack: {//attack
		this->attack(skill);
	}break;
	case skill_type::heal: {//heal
		this->heal(skill.value);
	}break;
	case skill_type::shield: {//shield
		this->shield(skill.value);
	}break;
	}
}

void Character::attack(const Skill const& skill) {
	prompt_input("輸入要攻擊怪物代號，放棄攻擊輸入0");
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
		tmprange!= no_path_found /*可以到達(無法到達回傳-87)*/ &&
		map->monster[index].show /*該怪物有出現*/ &&
		map->monster[index].show_in_room /*該怪物有出現在場上*/ &&
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

void Character::round_end() {//virtual//該回合結束後的重整(重設數值)
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
};
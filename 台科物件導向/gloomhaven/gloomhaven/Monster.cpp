#include "Gloom_Haven.h"

Monster::Monster() :Creature() {
	team_num = Team_num::monster;
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
	this->TmpShield = input.TmpShield;
	this->team_num = input.team_num;
	this->show_in_room = input.show_in_room;
	this->map = input.map;
	this->finished_show = input.finished_show;
	//elite系列---------------------------------
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
	case monster_status::disappear:show = false;break;//不出現
	case monster_status::normal:break;//普通怪
	case monster_status::elite: {//菁英怪
		elite = true;
		damage = elite_damage;
		max_life_value = elite_max_life_value;
		life_value = elite_max_life_value;
		range = elite_range;
	}break;
	default:break;
	}
}

void Monster::choose_card() {
	if (life_value <= 0 || !show_in_room || !show) {
		return;
	}
	//該種族怪物的第一隻(活著且出現)
	use_card[0] = find_card(race_card_number[name]);

}

void Monster::print(){
	if(life_value  <= 0 || !show_in_room || finished_show || !show){
		return;
	}
	cout << name << ' ' << setw(2) << setfill('0') << use_card[0].agility;
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch (use_card[0].skill_up[i].type)
		{
		case skill_type::move: {
			cout << " move " << use_card[0].skill_up[i].move_step;
		}break;
		case skill_type::attack: {
			cout << " attack " << use_card[0].skill_up[i].value;
			if (range != 0) {//遠程怪需印range
				cout << " range " << use_card[0].skill_up[i].range;
			}
		}break;
		case skill_type::heal: {
			cout << " heal " << use_card[0].skill_up[i].value;
		}break;
		case skill_type::shield: {
			cout << " shield " << use_card[0].skill_up[i].value;
		}break;
		default:
			break;
		}
	}
	cout << endl;
	for (int i = 0;i < map->monster_amount;i++) {
		if (map->monster + i == this || map->monster[i].name != name) continue;
		if (map->monster[i].life_value > 0 && map->monster[i].show_in_room) {
			map->monster[i].finished_show = true;
		}
	}
}
void Monster::action() {
	if (life_value <= 0 || !show_in_room) {
		return;
	}
	for (int i = 0;i < use_card[0].skill_up_amount;i++) {
		switch(use_card[0].skill_up[i].type) {
		case skill_type::move: {//move
			this->move(use_card[0].skill_up[i].move_step,0);//0可任意更改(不影響)
		}break;
		case skill_type::attack: {//attack
			this->attack(use_card[0].skill_up[i]);
		}break;
		case skill_type::heal: {//heal
			this->heal(use_card[0].skill_up[i].value);
		}break;
		case skill_type::shield: {//shield
			this->shield(use_card[0].skill_up[i].value);
		}break;
		default:break;
		}
	}
	if (!debug_mode) {
		cout << "請確認怪物的行動，按任意鍵以繼續(getch):" << endl;
		_getch();
	}
}

void Monster::attack(const Skill const& skill) {
	int min = map->row * map->col;//最大可能的步數
	int index = -1;//沒找到就是-1(可能角色死光了)
	for (int i = 0;i < map->character_amount;i++) {
		int tmpstep = map->a_star_path_step(this, map->character + i);
		if (tmpstep == no_path_found) {//無法攻擊到
			continue;
		}
		if (!map->in_vision(position, map->character[i].position)) {//沒有視野
			continue;
		}
		if (tmpstep < min) {//找出距離最小的角色
			index = i;
			min = tmpstep;
		}
		else if (tmpstep == min) {//距離一樣比第一張敏捷值
			if (creature_order_compare(map->character + i, map->character + index)) {
				index = i;
			}
		}
	}

	if (index == -1) {
		cout << "no one lock" << endl;
		return;
	}
	if (range != 0 && (range + skill.range) >= 1) {//遠程
		if (min > (range + skill.range)) {//自己的range加上卡牌的range
			cout << "no one lock" << endl;
			return;
		}
	}
	else {//近戰
		if (min > 1) {
			cout << "no one lock" << endl;
			return;
		}
	}

	cout << code << " lock " << map->character[index].code << " in distance " << min << endl;
	map->character[index].be_attack(code,skill.value + damage);//加上自己的攻擊力

}

void Monster::round_end() {//該回合結束後的重整(重設數值)
	//重洗標記
	TmpShield = 0;
	finished_choose = false;
	finished_show = false;
	if (life_value <= 0) {
		show = false;
		show_in_room = false;
		position.to_null();
	}
}

void Monster::to_discard() {
	if (life_value <= 0 || !show) {
		return;
	}
	find_card(race_card_number[name]).discard = true;
	if (find_card(race_card_number[name]).rewash_mark) {
		this->discard_to_hand();
	}
}

void Monster::set_debug() {
	if (race_card_number.find(name) == race_card_number.end()) {
		race_card_number.insert(make_pair(name,-1));
	}
}
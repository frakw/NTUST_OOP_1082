#include "Gloom_Haven.h"
#include "a_star_path.h"
Map::Map() {}
Map::Map(int in_row, int in_col) :row(in_row), col(in_col) {
	body = new char* [row] {};
	show = new bool* [row] {};
	for (int i = 0;i < row;i++) {
		body[i] = new char[col] {};
		show[i] = new bool[col] {};
	}
}
Map::~Map() {
	if (body != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] body[i];
		}
		delete[] body;
	}
	if (show != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] show[i];
		}
		delete[] show;
	}
	if (door_pos != nullptr) {
		delete[] door_pos;
	}
}
void Map::set(string input) {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			body[i][j] = input[i * col + j];
			if (body[i][j] == '3') {
				door_total_amount++;
			}
		}
	}
	door_pos = new Coord[door_total_amount];
	int index = 0;
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (body[i][j] == '3') {
				door_pos[index] = Coord( j,i );
				index++;
			}
		}
	}
}

bool Map::check_room() {
	bool open = false;
	if (!now_monster_amount()) {//若場上沒有怪物，檢查門是否開啟
		for (int i = 0;i < door_total_amount;i++) {//檢查門有沒有角色踩著，開啟後設為-1,-1
			if (door_pos[i].not_null()) {
				if (coord_in_body(door_pos[i]) != '3') {
					door_pos[i].to_null();
					open = true;//有開門
				}
			}
		}
	}
	for (int i = 0;i < row;i++) {//重設所有區域，可寫成reset funtion
		for (int j = 0;j < col;j++) {
			show[i][j] = false;
		}
	}
	this->fill_room(fill_start);//產生新的show
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].show && !monster[i].position.is_null() && monster[i].life_value > 0) {
			if (coord_in(show,monster[i].position)) {
				monster[i].show_in_room = true;
			}
			else {
				monster[i].show_in_room = false;
			}
		}
		else {
			monster[i].show_in_room = false;
		}
	}
	return open;
}

void Map::fill_room(Coord pos) {
	if (!coord_legal(pos)) {
		return;
	}
	if (coord_in(body,pos) == '0' || coord_in(show, pos)) {
		return;
	}
	else if (coord_in(body, pos) == '3') {
		coord_in(show, pos) = true;
		return;
	}
	else if(coord_in(body, pos) != '1' && coord_in(body, pos) != '2'){//角色或怪物
		for (int i = 0;i < door_total_amount;i++) {
			if (door_pos[i] == pos) {//若該地方為門，但有角色踩上去
				coord_in(show, pos) = true;
				return;
			}
		}
		coord_in(show, pos) = true;
	}
	else {//地板或障礙
		coord_in(show, pos) = true;
	}
	Coord direction[4] = {UP(pos),DOWN(pos),LEFT(pos),RIGHT(pos)};
	for (int i = 0;i < 4;i++) {
		this->fill_room(direction[i]);
	}
}

void Map::show_room() {
	this->update_all_creature();
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				cout << ((body[i][j] == '0') ? ' ' : body[i][j]);
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

void Map::show_choosing_room() {
	for (int i = 0;i < monster_amount;i++) {//copy from update
		if (!monster[i].show || monster[i].position.is_null()) continue;
		if (monster[i].life_value > 0) {
			coord_in(body, monster[i].position) = monster[i].code;
		}
		else {
			coord_in(body, monster[i].position) = '1';
		}
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.is_null()) continue;
		if (character[i].life_value > 0) {
			coord_in(body, character[i].position) = character[i].code;
		}
		else {
			coord_in(body, character[i].position) = '1';
		}
	}
	for (int i = 0;i < row;i++) {//do not call show_room function，no need to update
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				cout << ((body[i][j] == '0') ? ' ' : body[i][j]);
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

void Map::set_choosing_environment() {
	int min = row + col;
	int start_index = 0;
	for (int i = 0;i < 4;i++) {
		if (start_pos[i].y == -1) continue;
		int dis = start_pos[i].x + start_pos[i].y;
		if (dis < min) {
			start_index = i;
			min = dis;
		}
		else if (dis == min) {
			if (start_pos[i].y < start_pos[start_index].y) {
				start_index = i;
			}
		}
	}
	for (int i = 0;i < 4;i++) {//可選位置設為_ *
		if (start_pos[i].y != -1 && start_pos[i].x != -1) {
			body[start_pos[i].y][start_pos[i].x] = start_index != i?'_':'*';
		}
	}
	star_pos = start_pos[start_index];

}

Coord& Map::find_pos(Coord* check,int max,Coord pos) {
	for (int i = 0;i < max;i++) {
		if (check[i] == pos) {
			return check[i];
		}
	}
}

void Map::choose_pos(int index, string step) {
	this->set_choosing_environment();//設置底線與選擇星星位置
	Coord now = star_pos;
	coord_in(body, now) = '_';//暫時設為底線，方便wasd
	for (int i = 0;i < step.length();i++) {
		switch (step[i]) {
		case'w': {
			if (now.y - 1 >= 0) {
				if (coord_in(body, now.up()) == '_') {
					now = now.up();
				}
			}
		}break;
		case'a': {
			if (now.x - 1 >= 0) {
				if (coord_in(body, now.left()) == '_') {
					now = now.left();
				}
			}
		}break;
		case's': {
			if (star_pos.y + 1 < row) {
				if (coord_in(body, now.down()) == '_') {
					now = now.down();
				}
			}
		}break;;
		case'd': {
			if (star_pos.x + 1 < col) {
				if (coord_in(body, now.right()) == '_') {
					now = now.right();
				}
			}
		}break;
		case 'e':
		default:break;
		}
	}
	character[index].position = now;
	find_pos(start_pos, 4, now).to_null();
	if (index == character_amount - 1) {//最後一個角色選擇完後，將所有底線改回1
		for (int i = 0;i < 4;i++) {
			if (start_pos[i].not_null()) {
				coord_in(body, start_pos[i]) = '1';
			}
		}
	}
	else {
		this->set_choosing_environment();//設置底線與選擇星星位置
	}
}

void Map::update_all_creature() {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				if (body[i][j] != '0' && body[i][j] != '1' && body[i][j] != '2' && body[i][j] != '3') {
					body[i][j] = '1';//先把所有生物位置設為地板
				}
			}
		}
	}
	for (int i = 0;i < door_total_amount;i++) {//門
		if (door_pos[i].not_null()) {
			coord_in(body,door_pos[i]) = '3';
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (!monster[i].show || monster[i].position.is_null() || monster[i].life_value <= 0) continue;
		coord_in(body, monster[i].position) = monster[i].code;
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.is_null() || character[i].life_value <= 0) continue;
		coord_in(body, character[i].position) = character[i].code;
	}
}

int Map::now_monster_amount() {
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0 && monster[i].show_in_room && monster[i].show) {
			count++;
		}
	}
	return count;
}

int Map::door_amount() {
	int count = 0;
	for (int i = 0;i < door_total_amount;i++) {
		if (door_pos[i].not_null()) {
			count++;
		}
	}
	return count;
}

int Map::now_door_amount() {
	int count = 0;
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				if (body[i][j] == '3') {
					count++;
				}
			}
		}
	}
	return count;
}

Creature* Map::creature_in(Coord pos) {
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position == pos && character[i].life_value > 0) {
			return character + i;
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].position == pos && monster[i].life_value>0 && monster[i].show && monster[i].show_in_room) {
			return monster + i;
		}
	}
	return nullptr;
}

char& Map::coord_in_body(Coord pos) {
	if (!coord_legal(pos)) {
		cout << "coord ilegal!!" << endl;
		return body[0][0];
	}
	return body[pos.y][pos.x];
}


bool Map::in_vision(Coord a, Coord b) {//線性差值法
	Coord check;
	if (b.x < a.x) {
		swap(a, b);//小的x在a，大的x在b
	}
	else if (b.x == a.x) {//垂直斜率無限大，用y做
		if (b.y < a.y) {
			swap(a, b);
		}
		check.x = a.x;
		for (int i = a.y;i < b.y;i++) {
			check.y = i;
			if (coord_in_body(check) == '0') {
				return false;
			}
		}
		return true;
	}
	//用x做
	double slope = ((double)b.y- (double)a.y) / ((double)b.x- (double)a.x);//m斜率
	double bb = (double)a.y - slope * (double)a.x;//y=mx+b
	for (int i = a.x;i < b.x;i++) {
		check.x = i;
		check.y = ceil((double)i* slope + bb);
		if (coord_in_body(check) == '0') {
			return false;
		}
	}
	return true;
}


void Map::check() {//角色行動前，輸入check，要列出所有角色與怪物的hp與防禦值
	for (int i = 0;i < character_amount;i++) {
		if (character[i].life_value > 0) {
			character[i].check();
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0 && monster[i].show_in_room && monster[i].show) {
			monster[i].check();
		}
	}
}

bool Map::coord_legal(Coord a) {
	return (a.x < col) && (a.x >= 0) && (a.y < row) && (a.y >= 0);
}
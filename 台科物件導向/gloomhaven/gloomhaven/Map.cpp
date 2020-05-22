#include "Gloom_Haven.h"
#include "a_star_path.h"
Map::Map() {}
Map::Map(int in_row, int in_col) :row(in_row), col(in_col) {
	body = new char* [row] {};
	show = new bool* [row] {};
	recursive_dedicated = new bool* [row] {};
	for (int i = 0;i < row;i++) {
		body[i] = new char[col] {};
		show[i] = new bool[col] {};
		recursive_dedicated[i] = new bool[col] {};
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
	if (recursive_dedicated != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] recursive_dedicated[i];
		}
		delete[] recursive_dedicated;
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
				door_pos[index] = { j,i };
				index++;
			}
		}
	}
}

void Map::check_room() {
	for (int i = 0;i < row;i++) {//重設所有區域
		for (int j = 0;j < col;j++) {
			show[i][j] = false;
		}
	}
	this->fill_room(fill_start);
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].show) {
			if (show[monster[i].position.y][monster[i].position.x]) {
				monster[i].show_in_room = true;
			}
		}
	}
}

void Map::fill_room(Coord pos) {
	if (pos.x >= col || pos.x < 0 || pos.y >= row || pos.y < 0) {
		return;
	}
	if (body[pos.y][pos.x] == '0' || show[pos.y][pos.x]) {
		return;
	}
	else if (body[pos.y][pos.x] == '3') {
		show[pos.y][pos.x] = true;
		return;
	}
	else {
		show[pos.y][pos.x] = true;
	}
	Coord direction[4] = { {pos.x,pos.y - 1},{pos.x,pos.y + 1} ,{pos.x - 1 ,pos.y} ,{pos.x + 1,pos.y} };
	for (int i = 0;i < 4;i++) {
		this->fill_room(direction[i]);
	}
}

void Map::show_room() {
	this->update_all_creature();
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				switch (body[i][j]) {
				case'0':cout << ' ';break;
				default:cout << body[i][j];break;
				}
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
		if (!monster[i].show || monster[i].position.y == -1 || monster[i].position.x == -1) continue;
		if (monster[i].life_value > 0) {
			body[monster[i].position.y][monster[i].position.x] = monster[i].code;
		}
		else {
			body[monster[i].position.y][monster[i].position.x] = '1';
		}
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.y == -1 || character[i].position.x == -1) continue;
		if (character[i].life_value > 0) {
			body[character[i].position.y][character[i].position.x] = character[i].code;
		}
		else {
			body[character[i].position.y][character[i].position.x] = '1';
		}
	}
	for (int i = 0;i < row;i++) {//copy from show
		for (int j = 0;j < col;j++) {
			if (show[i][j]) {
				switch (body[i][j]) {
				case'0':cout << ' ';break;
				default:cout << body[i][j];break;
				}
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
			if (start_index != i) {
				body[start_pos[i].y][start_pos[i].x] = '_';
			}
			else {
				body[start_pos[i].y][start_pos[i].x] = '*';
			}
		}
	}
	star_pos = start_pos[start_index];

}

Coord& Map::find_pos(Coord* check,int max,Coord pos) {
	for (int i = 0;i < max;i++) {
		if (check[i].x == pos.x && check[i].y == pos.y) {
			return check[i];
		}
	}
}

void Map::choose_pos(int index, string step) {
	this->set_choosing_environment();//設置底線與選擇星星位置
	Coord now = star_pos;
	body[now.y][now.x] = '_';//暫時設為底線，方便wasd
	for (int i = 0;i < step.length();i++) {
		switch (step[i]) {
		case'w': {
			if (now.y - 1 >= 0) {
				if (body[now.y - 1][now.x] == '_') {
					now = { now.x, now.y-1 };
				}
			}
		}break;
		case'a': {
			if (now.x - 1 >= 0) {
				if (body[now.y][now.x-1] == '_') {
					now = { now.x-1, now.y };
				}
			}
		}break;
		case's': {
			if (star_pos.y + 1 < row) {
				if (body[now.y + 1][now.x] == '_') {
					now = { now.x, now.y+1};
				}
			}
		}break;;
		case'd': {
			if (star_pos.x + 1 < col) {
				if (body[now.y][now.x+1] == '_') {
					now = { now.x+1, now.y };
				}
			}
		}break;
		case 'e':
		default:break;
		}
	}
	//body[now.y][now.x] = character[index].code;
	character[index].position = now;
	find_pos(start_pos, 4, now) = { -1,-1 };
	if (index == character_amount - 1) {//最後一個角色選擇完後，將所有底線改回1
		for (int i = 0;i < 4;i++) {
			if (start_pos[i].y != -1 && start_pos[i].x != -1) {
				body[start_pos[i].y][start_pos[i].x] = '1';
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
		if (door_pos[i].x != -1 && door_pos[i].y != -1) {
			body[door_pos[i].y][door_pos[i].x] = '3';
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (!monster[i].show || monster[i].position.y == -1 || monster[i].position.x == -1) continue;
		if (monster[i].life_value > 0) {
			body[monster[i].position.y][monster[i].position.x] = monster[i].code;
		}
	}
	for (int i = 0;i < character_amount;i++) {
		if (character[i].position.y == -1 || character[i].position.x == -1) continue;
		if (character[i].life_value > 0) {
			body[character[i].position.y][character[i].position.x] = character[i].code;
		}
	}
}

int Map::now_monster_amount() {
	int count = 0;
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].life_value > 0) {
			if (show[monster[i].position.y][monster[i].position.x]) {
				count++;
			}
		}
	}
	return count;
}

int Map::door_amount() {
	int count = 0;
	for (int i = 0;i < door_total_amount;i++) {
		if (door_pos[i].x != -1 && door_pos[i].y != -1) {
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
		if (character[i].position.x == pos.x && character[i].position.y == pos.y) {
			return character + i;
		}
	}
	for (int i = 0;i < monster_amount;i++) {
		if (monster[i].position.x == pos.x && monster[i].position.y == pos.y) {
			return monster + i;
		}
	}
	return nullptr;
}

char& Map::coord_in_body(Coord pos) {
	return body[pos.y][pos.x];
}


//bool Map::in_range(Creature* main,Coord a, Coord b, int count) {//計算2座標間的步數
//	A_star_path_step(this,make_pair(a,b));
//	return false;
//	if (a.x >= col || a.x < 0 || a.y >= row || a.y < 0 || count<0) {
//		return false;
//	}
//	if (body[a.y][a.x] == '0' || creature_in(a)->team_num!=main->team_num) {
//		return false;
//	}
//	if (a.x == b.x && a.y == b.y) {
//		return true;
//	}
//	if (!recursive_dedicated[a.y][a.x]) {
//		recursive_dedicated[a.y][a.x] = true;
//	}
//	else {
//		return false;
//	}
//	Coord direction[4] = { {a.x,a.y-1},{a.x,a.y+1},{a.x-1,a.y},{a.x+1,a.y} };
//	for (int i = 0;i < 4;i++) {
//		if (in_range(main,direction[i], b, count - 1)) {
//			return true;
//		}
//	}
//	return false;
//}

void Map::copy_to(bool** a, bool** b) {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			a[i][j] = b[i][j];
		}
	}
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

void Map::reset_in_range() {//in_range重設全部為false
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < row;j++) {
			recursive_dedicated[i][j] = false;
		}
	}
}
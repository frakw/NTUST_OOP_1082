#include "Gloom_Haven.h"

int Manhattan_distance(Coord,Coord);

Grid::Grid(Coord in, Grid* the_father, Coord end_point) {
	this->coord = in;
	if (the_father != nullptr) {
		this->calc_val(the_father, end_point);
	}
}

void Grid::calc_val(Grid* the_father, Coord end_point) {
	int tmp = Manhattan_distance(the_father->coord, this->coord);
	if (father == nullptr) {
		this->father = the_father;
		G = father->G + tmp;
		H = Manhattan_distance(end_point, this->coord);
		F = G + H;
	}
	else {
		if (tmp < G) {
			this->father = the_father;
			G = father->G + tmp;
			F = G + H;
		}
	}
}

//檢查vector內有無要check的座標
int exist_in(vector<Grid*>* data_ptr, Coord check) {
	for (int i = 0;i < data_ptr->size();i++) {
		if ((*data_ptr)[i]->coord == check) {
			return i;
		}
	}
	return -1;
}

//A星演算法
int Map::a_star_path_step(Creature* coord, Creature* dest) {
	vector<Grid*> close_list;
	vector<Grid*> open_list;
	Grid* current = new Grid(coord->position, nullptr, dest->position);
	open_list.push_back(current);
	do {
		if (open_list.empty()) {
			return no_path_found;//找不到路徑，無法到達回傳-87
		}
		int min = open_list.front()->F;
		int pos = 0;
		for (int i = 1;i < open_list.size();i++) {
			if (open_list[i]->F < min) {
				pos = i;
				min = open_list[i]->F;
			}
		}
		close_list.push_back(open_list[pos]);
		open_list.erase(open_list.begin() + pos);
		current = close_list.back();
		Coord direction[4] = { UP(current->coord),DOWN(current->coord),LEFT(current->coord),RIGHT(current->coord) };
		for (int i = 0;i < 4;i++) {
			char now_char = this->coord_in_body(direction[i]);
			Creature* now_life = this->creature_in(direction[i]);
			if (now_char == map_obj::wall) {//排除牆壁，!=改==修復bug
				continue;
			}
			if (exist_in(&close_list, direction[i]) == -1) {
				int pos2 = exist_in(&open_list, direction[i]);
				if (pos2 == -1) {
					open_list.push_back(new Grid(direction[i], current, dest->position));
				}
				else {
					open_list[pos2]->calc_val(current, dest->position);
				}
			}
		}
	} while (current->coord != dest->position);
	int count = 1;
	current = current->father;
	while (current->father!=nullptr) {
		current = current->father;
		count++;
	}
	for (int i = 0;i < close_list.size();i++) {
		delete[] close_list[i];
		close_list[i] = nullptr;
	}
	for (int i = 0;i < open_list.size();i++) {
		delete[] open_list[i];
		open_list[i] = nullptr;
	}
	return count;
}
int Manhattan_distance(Coord a, Coord b) {//曼哈頓距離
	return abs(a.x - b.x) + abs(a.y - b.y);
}

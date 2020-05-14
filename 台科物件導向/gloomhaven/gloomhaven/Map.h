#pragma once
#include "Monster.h"
#include "Character.h"

class Map {
public:
	Map(int in_row, int in_col) :row(in_row), col(in_col) {}
	void add_character(Character input) {
		
	}
	void add_monster(Monster input) {

	}
	int row, col;
	Character* player;
	Monster*	enemy;
};
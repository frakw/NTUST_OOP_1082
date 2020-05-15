#pragma once
#include "Monster.h"
#include "Character.h"
#include <utility>
#include <string>
typedef struct {
	int x, y;
}Coord;
class Map {
public:
	Map() {}
	Map(int in_row, int in_col) :row(in_row), col(in_col) {
		body = new char* [row] {};
		for (int i = 0;i < row;i++) {
			body[i] = new char[col] {};
		}
	}
	~Map() {
		if (body != nullptr) {
			for (int i = 0;i < row;i++) {
				delete[] body[i];
			}
			delete[] body;
		}
	}
	void set(string input) {
		for (int i = 0;i < row;i++) {
			for (int j = 0;j < col;j++) {
				body[i][j] = input[i * col + j];
			}
		}
	}
	int row=0, col=0;
	char** body = nullptr;
	Coord start_pos[4];//¥i¿ï¦ì¸m
	Character* player = nullptr;
	Monster* enemy = nullptr;
};
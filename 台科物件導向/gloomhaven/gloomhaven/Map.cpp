#include "Gloom_Haven.h"

Map::Map() {}
Map::Map(int in_row, int in_col) :row(in_row), col(in_col) {
	body = new char* [row] {};
	for (int i = 0;i < row;i++) {
		body[i] = new char[col] {};
	}
}
Map::~Map() {
	if (body != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] body[i];
		}
		delete[] body;
	}
}
void Map::set(string input) {
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			body[i][j] = input[i * col + j];
		}
	}
}
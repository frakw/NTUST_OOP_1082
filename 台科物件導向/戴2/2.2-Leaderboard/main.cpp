#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include<cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::endl;
typedef struct player_stc
{
	std::string name;
	int score;
}player;
void print_player(player);
void getHighScores(std::vector<player>*);
bool compare_score(const player&, const player&);
void swap(void*, void*, size_t);
int main() {
	int i = 0;
	std::vector<player> member;
	player temp;
	while (!std::cin.eof()) {//eof ctrl+z
		std::cin >> temp.name;
		std::cin >> temp.score;
		member.push_back(temp);
	}
	//getHighScores(&member);//---->way 1
	std::sort(member.begin(), member.end(), compare_score);//---->way 2
	for (i = 0;i < 3;i++) {
		print_player(member[i]);
	}
	system("pause");
	return 0;
}
void print_player(player a) {
	std::cout << a.name << endl << a.score << endl;
}

void getHighScores(std::vector<player>* arr) {
	for (int i = 0; i < arr->size(); i++) {
		for (int j = 0; j < i; j++) {
			if ((*arr)[j].score < (*arr)[i].score) {
				swap(&(*arr)[j], &(*arr)[i], sizeof(player));
			}
		}
	}
}

bool
compare_score(const player& a, const player& b)
{
	return a.score > b.score;
}

void swap(void* vp1, void* vp2, size_t size)
{
	char* buf = (char*)malloc(size);
	memcpy(buf, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buf, size);
	free(buf);
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using std::endl;
typedef struct _player
{
	std::string name;
	int score;
}player;
//void getHighScores(std::vector<player>);
//void swap(void*, void*, size_t);
void print_player(player);
int main() {
	int i = 0;
	std::vector<player> member;
	player temp;
	for (i = 0;i < 3;i++) {
		std::cin >> temp.name;
		std::cin >> temp.score;
		member.push_back(temp);
	}
	//std::sort(member.begin(), member.end());
	for (i = 0;i < 3;i++) {
		//print_player(member[i]);
	}
	system("pause");
	return 0;
}
void print_player(player a) {
	std::cout << a.name << endl << a.score << endl;
}
//void swap(void* vp1, void* vp2, size_t size)
//{
//	char* buf = (char*)malloc(size);
//	memcpy(buf, vp1, size);
//	memcpy(vp1, vp2, size);
//	memcpy(vp2, buf, size);
//	free(buf);
//}
//
//void getHighScores(std::vector<player> arr) {
//	for (int i = 0; i < arr.size(); i++) {
//		for (int j = 0; j < i; j++) {
//			if (arr[j].score > arr[i].score) {
//				swap(&arr[j], &arr[i],sizeof(player));
//			}
//		}
//	}
//}
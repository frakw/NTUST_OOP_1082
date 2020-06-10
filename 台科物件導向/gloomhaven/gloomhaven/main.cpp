#include "Gloom_Haven.h"
using namespace std;
#include <iostream>
int main(int argc, char** argv) {
	srand(time(0));
	TXT preprocess;
	string map_filename;
	string play;
	string input[4];
	input[1] = "./character3.txt";
	input[2] = "./monster3.txt";
	input[3] = "1";
#ifdef command_line
	int start_index = 1;
	if (argc != 4) {
		cout << "error command line input !" << endl;
		return 0;
	}
	preprocess.read_character(argv[start_index + 0]);
	preprocess.read_monster(argv[start_index + 1]);
	debug_mode = (bool)atoi(argv[start_index + 2]);
#else
	preprocess.read_character(input[1]);
	preprocess.read_monster(input[2]);
	debug_mode = (bool)stoi(input[3]);
#endif

	while (1) {
		prompt_input("輸入遊玩指令play或離開指令exit");
		mygetline(cin, play);
		while(play != "play" && play != "exit") {
			cout << "error command input again!(play or exit)" << endl;
			mygetline(cin, play);
		}
		if (play == "exit") {
			break;
		}
		preprocess.input_character_data();
		prompt_input("輸入地圖txt檔案路徑");
		mygetline(cin, map_filename);
		preprocess.read_map(map_filename);
		Gloom_Haven game(preprocess.return_tuple());

		game.start();
	}
	prompt_input("bye bye~~");
	return 0;
}

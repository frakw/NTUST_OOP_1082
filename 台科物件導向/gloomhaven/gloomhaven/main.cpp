#include "Gloom_Haven.h"
using namespace std;
#include <iostream>
//#define command_line
int main(int argc, char** argv) {
	srand(time(NULL));
	TXT preprocess;
	string map_filename;
	string play;
	string input[4];
	input[1] = "./character1.txt";
	input[2] = "./monster1.txt";
	input[3] = "1";
#ifdef command_line
	if (argc != 4) {
		cout << "error command line input !" << endl;
	}
	preprocess.read_character(argv[1]);
	preprocess.read_monster(argv[2]);
#else
	preprocess.read_character(input[1]);
	preprocess.read_monster(input[2]);
#endif

	;
	while (cin >> play) {
		while(play != "play" && play != "exit") {
			cout << "error command input again!(play or exit)" << endl;
			cin >> play;
		}
		if (play == "exit") {
			break;
		}
		preprocess.input_character_data();
		cin.ignore();
		cout << "input map file name" << endl;
		getline(cin, map_filename);
		cout << map_filename << endl;
		preprocess.read_map(map_filename);
#ifdef command_line
		Gloom_Haven game(preprocess.return_tuple(), (bool)atoi(argv[3]));
#else
		Gloom_Haven game(preprocess.return_tuple(), (bool)atoi(input[3].c_str()));
#endif
		game.start();
		cout << "next turn" << endl;
	}
	cout << "bye bye~~";
	return 0;
}
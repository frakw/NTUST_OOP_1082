#include "Gloom_Haven.h"
using namespace std;
#include <iostream>
int main(int argc, char** argv) {
	//Gloom_Haven game;
	//game.start();
	TXT file("character1.txt");
	file.read_character();
	file.return_tuple();
	return 0;
}
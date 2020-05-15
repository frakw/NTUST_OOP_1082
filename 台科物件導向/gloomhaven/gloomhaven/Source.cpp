#include "Gloom_Haven.h"
using namespace std;
#include <iostream>
int main(int argc, char** argv) {
	//Gloom_Haven game;
	//game.start();
	TXT file("map1.txt");
	file.read_map();
	return 0;
}
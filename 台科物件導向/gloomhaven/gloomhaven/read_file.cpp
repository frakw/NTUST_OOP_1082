#include "read_file.h"
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


tuple<Character*, Monster*, Map*> TXT::return_tuple() {
	Character* tmpC;
	int Character_amount;
	string Character_name;
	int index;
	cin >> Character_amount;
	tmpC = new Character[Character_amount];
	for (int i = 0;i < Character_amount;i++) {
		cin >> Character_name;
		for (int j = 0;j < total_chr;j++) {
			if (character[j].name == Character_name) {
				tmpC[i] = character[j];
				for (int k = 0;k < character[j].card_amount;k++) {
					cin >> index;
					tmpC[i].card[k] = character[j].card[index];
				}
			}
		}
	}

	return make_tuple(tmpC, monster, this->read_map());
}


void TXT::read_character() {

}

void TXT::read_monster() {

}


Map* TXT::read_map() {

}

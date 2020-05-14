#include "read_file.h"
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int skill_input(string input,Skill** card);

tuple<Character*, Monster*, Map*> TXT::return_tuple() {
	if (character == nullptr) {
		this->read_character();
	}
	Character* tmpC;
	int Character_amount;
	string Character_name;
	int number;
	cin >> Character_amount;
	tmpC = new Character[Character_amount];
	for (int i = 0;i < Character_amount;i++) {
		cin >> Character_name;
		for (int j = 0;j < total_chr;j++) {
			if (character[j].name == Character_name) {
				tmpC[i] = character[j];
				for (int k = 0;k < character[j].card_amount;k++) {
					cin >> number;
					for (int m = 0; m < character[j].card_total;m++) {
						if (number == character[j].card[m].number) {
							tmpC[i].card[k] = character[j].card[m];
							break;
						}
					}
					
				}
			}
		}
	}


	//for (int i = 0;i < Character_amount;i++) {
	//	std::cout << tmpC[i].name << ' ' << tmpC[i].life_value << ' ' << tmpC[i].card_amount << ' ' << tmpC[i].card_total<<endl;
	//	for (int j = 0;j < tmpC[i].card_amount;j++) {
	//		for (int k = 0;k < tmpC[i].card[j].skill_up_amount;k++) {
	//			std::cout << tmpC[i].card[j].skill_up[k].type << endl;
	//		}
	//	}
	//}
	return make_tuple(tmpC, monster, this->read_map());
}


void TXT::read_character() {
	fstream file;
	file.open(filename, ios::in);
	file >> total_chr;
	character = new Character[total_chr];
	for (int i = 0;i < total_chr;i++) {
		file>> character[i].name
			>> character[i].life_value
			>> character[i].card_amount
			>> character[i].card_total;
		file.ignore();
		character[i].card = new Card[character[i].card_total];
		for (int j = 0;j < character[i].card_total;j++) {
			string line;
			getline(file,line);
			stringstream ss(line);
			string type="";
			char tmp;
			ss >> character[i].card[j].number
			   >> character[i].card[j].agility;
			string process="";
			ss >> type;
			while (type != "-") {//bug here
				process = process + " " + type;
				ss >> type;
			}
			character[i].card[j].skill_up_amount = skill_input(process, &character[i].card[j].skill_up);
			
			process.clear();
			while (!ss.eof()) {
				ss >> type;
				process = process + " " + type;
			}
			character[i].card[j].skill_down_amount = skill_input(process, &character[i].card[j].skill_down);
		}
	}
}

int skill_input(string input,Skill** skill) {
	stringstream ss(input);
	string type;
	int val;
	int count=0;
	while (!ss.eof()) {
		ss >> type >> val;
		if (type != "range") {
			count++;
		}
	}
	ss.clear();
	ss.str("");
	ss << input;
	*skill = new Skill[count];
	int i = 0;
	while (!ss.eof()) {
		ss >> type >> val;
		if (type != "range") {
			(*skill)[i].set(type,val);
			i++;
		}
		else {
			(*skill)[i-1].range = val;
		}
	}
	return count;//skill_amount;
}

void TXT::read_monster() {

}


Map* TXT::read_map() {
	return nullptr;
}

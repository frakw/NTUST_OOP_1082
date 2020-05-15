
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "basic.h"
#include "Character.h"
#include "Monster.h"
#include "map.h"
#include "read_file.h"

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

int skill_input(string input,Skill** skill) {//for character only
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
	fstream file;
	file.open(filename, ios::in);
	file >> total_mon;
	monster = new Monster[total_mon];
	for (int i = 0;i < total_mon;i++) {
		file >> monster[i].name
			 >> monster[i].life_value
			 >> monster[i].damage
			 >> monster[i].range
			 >> monster[i].elite_life_value
			 >> monster[i].elite_damage
			 >> monster[i].elite_range;
		monster[i].card = new Card[6];
		string trash;
		for (int j = 0;j < 6;j++) {
			file >> trash
				 >> monster[i].card[j].number
				 >> monster[i].card[j].agility;
			string process="";
			string type="";
			string value;
			file >> type;
			while (type != "r" && type != "d") {
				process = process + " " + type;
				file >> type;
			}
			monster[i].card[j].rewash_mark = (type == "r");
			stringstream ss(process);
			int count = 0,x = 0;
			while (!ss.eof()) {
				ss >> type >> value;
				if (type != "range") {
					count++;
				}
			}
			monster[i].card[j].skill_up = new Skill[count];
			monster[i].card[j].skill_up_amount = count;
			ss.clear();
			ss.str("");
			ss << process;
			while(!ss.eof()){
				ss >> type >> value;
				if (type != "range") {
					if (type != "move") {
						monster[i].card[j].skill_up[x].set(type, atoi(value.c_str()));
					}
					else {
						monster[i].card[j].skill_up[x].set(type, value.length());
						monster[i].card[j].skill_up[x].move_step = value;
					}
					x++;
				}
				else {
					monster[i].card[j].skill_up[x - 1].range = atoi(value.c_str());
				}
			}
		}
	}
}


Map* TXT::read_map() {//call this func after above two func 
	fstream file;
	file.open(filename, ios::in);

	int row, col;
	file >>row >> col;
	Map* map = new Map(row,col);
	file.ignore();
	string tmp,out="";
	for (int i = 0;i < row;i++) {
		file >> tmp;
		out += tmp;
	}
	map->set(out);
	for (int i = 0;i < 4;i++) {
		file >> map->start_pos[i].x >> map->start_pos[i].y;
	}
	int Monster_amount;
	string Monster_name;
	file >> Monster_amount;
	monput = new Monster[Monster_amount];
	for (int i = 0;i < Monster_amount;i++) {
		for (int j = 0;j < total_mon;j++) {
			if (Monster_name == monster[j].name) {
				int two, three,four;
				monput[i] = monster[j];
				file >> monput[i].position.x >> monput[i].position.y;
				file >> two >> three >> four;
				switch (total_chr)
				{
				case 2:monput[i].switch_status(two);break;
				case 3:monput[i].switch_status(three);break;
				case 4:monput[i].switch_status(four);break;
				default:break;
				}
			}
		}
	}
	return map;
}


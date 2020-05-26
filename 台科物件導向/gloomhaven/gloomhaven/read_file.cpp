#include "Gloom_Haven.h"

using namespace std;

int skill_input(string input,Skill** card);




tuple<Character*,int, Monster*,int, Map*> TXT::return_tuple() {
	for (int i = 0;i < Character_amount;i++) {//地圖指標存入所有生物，方便之後的行動action
		chrput[i].map = map;
	}
	for (int i = 0;i < Monster_amount;i++) {//地圖指標存入所有生物，方便之後的行動action
		monput[i].map = map;
	}
	return make_tuple(chrput,Character_amount, monput,Monster_amount, map);
}


void TXT::read_character(string filename) {
	fstream file;
	open_file(file, filename);
	file >> total_chr;
	character = new Character[total_chr];
	for (int i = 0;i < total_chr;i++) {
		file>> character[i].name
			>> character[i].max_life_value
			>> character[i].card_amount
			>> character[i].card_total;
		character[i].life_value = character[i].max_life_value;
		character[i].team_num = 0;//角色為0
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
	file.close();
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
			(*skill)[i].range = 1;//重要，角色range都設為1
			i++;
		}
		else {
			(*skill)[i-1].range = val;
		}
	}
	return count;//skill_amount;
}

void TXT::read_monster(string filename) {
	fstream file;
	open_file(file, filename);
	file >> total_mon;
	monster = new Monster[total_mon];
	for (int i = 0;i < total_mon;i++) {
		file >> monster[i].name
			 >> monster[i].max_life_value
			 >> monster[i].damage
			 >> monster[i].range
			 >> monster[i].elite_max_life_value
			 >> monster[i].elite_damage
			 >> monster[i].elite_range;
		monster[i].life_value = monster[i].max_life_value;
		monster[i].card_amount = 6;//記得要加
		monster[i].team_num = 1;//怪物為1
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
	file.close();
}

void TXT::input_character_data() {
	cout << "請輸入出場角色數量:"<<endl;
	string Character_name;
	int number;
    Character_amount = character_amount_input();
	char code = 'A';
	chrput = new Character[Character_amount];
	for (int i = 0;i < Character_amount;i++) {
		character_data_input(chrput[i], character, total_chr, code);
		code++;
	}
}


void TXT::read_map(string filename) {//call this func after above two func 
	fstream file;
	open_file(file, filename);
	if (map != nullptr) {
		delete map;
		map = nullptr;
	}
	int row, col;
	file >>row >> col;
	map = new Map(row,col);
	string tmp,out="";
	for (int i = 0;i < row;i++) {
		file >> tmp;
		out += tmp;
	}
	map->set(out);
	for (int i = 0;i < 4;i++) {
		file >> map->start_pos[i].x >> map->start_pos[i].y;
	}
	map->fill_start = map->start_pos[0];
	char code = 'a';
	string Monster_name;
	file >> Monster_amount;
	monput = new Monster[Monster_amount];
	for (int i = 0;i < Monster_amount;i++) {
		file >> Monster_name;//忘記加
		for (int j = 0;j < total_mon;j++) {
			if (Monster_name == monster[j].name) {
				int two, three,four;
				monput[i] = monster[j];
				monput[i].code = code;
				code++;
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
	file.close();
}


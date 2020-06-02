#include "Gloom_Haven.h"

using namespace std;

int skill_input(string input,Skill** card);

tuple<Character*,int, Monster*,int, Map*> TXT::return_tuple() {
	for (int i = 0;i < character_amount;i++) {//地圖指標存入所有生物，方便之後的行動action
		character_output[i].map = map;
	}
	for (int i = 0;i < monster_amount;i++) {//地圖指標存入所有生物，方便之後的行動action
		monster_output[i].map = map;
	}
	return make_tuple(character_output,character_amount, monster_output,monster_amount, map);
}


void TXT::read_character(string filename) {
	fstream file;
	open_file(file, filename);
	file >> chr_db_amount;
	character_db = new Character[chr_db_amount];
	for (int i = 0;i < chr_db_amount;i++) {
		file>> character_db[i].name
			>> character_db[i].max_life_value
			>> character_db[i].card_amount
			>> character_db[i].card_total;
		character_db[i].life_value = character_db[i].max_life_value;
		character_db[i].team_num = 0;//角色為0
		file.ignore();
		character_db[i].card = new Card[character_db[i].card_total];
		for (int j = 0;j < character_db[i].card_total;j++) {
			string line;
			getline(file,line);
			stringstream ss(line);
			string type="";
			char tmp;
			ss >> character_db[i].card[j].number
			   >> character_db[i].card[j].agility;
			string process="";
			ss >> type;
			while (type != "-") {//bug here
				process = process + " " + type;
				ss >> type;
			}
			character_db[i].card[j].skill_up_amount = skill_input(process, &character_db[i].card[j].skill_up);
			
			process.clear();
			while (!ss.eof()) {
				ss >> type;
				process = process + " " + type;
			}
			character_db[i].card[j].skill_down_amount = skill_input(process, &character_db[i].card[j].skill_down);
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
	return count;
}

void TXT::read_monster(string filename) {
	fstream file;
	open_file(file, filename);
	file >> mon_db_amount;
	monster_db = new Monster[mon_db_amount];
	for (int i = 0;i < mon_db_amount;i++) {
		file >> monster_db[i].name
			 >> monster_db[i].max_life_value
			 >> monster_db[i].damage
			 >> monster_db[i].range
			 >> monster_db[i].elite_max_life_value
			 >> monster_db[i].elite_damage
			 >> monster_db[i].elite_range;
		monster_db[i].life_value = monster_db[i].max_life_value;
		monster_db[i].card_amount = 6;//記得要加，怪物卡牌皆為6張
		monster_db[i].team_num = 1;//怪物為1
		monster_db[i].card = new Card[6];
		string trash;
		for (int j = 0;j < 6;j++) {
			file >> trash
				 >> monster_db[i].card[j].number
				 >> monster_db[i].card[j].agility;
			string process="";
			string type="";
			string value;
			file >> type;
			while (type != "r" && type != "d") {
				process = process + " " + type;
				file >> type;
			}
			monster_db[i].card[j].rewash_mark = (type == "r");
			stringstream ss(process);
			int count = 0,x = 0;
			while (!ss.eof()) {
				ss >> type >> value;
				if (type != "range") {
					count++;
				}
			}
			monster_db[i].card[j].skill_up = new Skill[count];
			monster_db[i].card[j].skill_up_amount = count;
			ss.clear();
			ss.str("");
			ss << process;
			while(!ss.eof()){
				ss >> type >> value;
				if (type != "range") {
					if (type != "move") {
						monster_db[i].card[j].skill_up[x].set(type, atoi(value.c_str()));
					}
					else {
						monster_db[i].card[j].skill_up[x].set(type, value.length());
						monster_db[i].card[j].skill_up[x].move_step = value;
					}
					x++;
				}
				else {
					monster_db[i].card[j].skill_up[x - 1].range = atoi(value.c_str());
				}
			}
		}
	}
	file.close();
}

void TXT::input_character_data() {
    character_amount = character_amount_input();
	char code = 'A';
	character_output = new Character[character_amount];
	for (int i = 0;i < character_amount;i++) {
		character_data_input(character_output[i], character_db, chr_db_amount, code);
		code++;
	}
}


void TXT::read_map(string filename) {//call this func after above two func 
	fstream file;
	open_file(file, filename);
	mydelete_single(map);
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
	file >> monster_amount;
	monster_output = new Monster[monster_amount];
	for (int i = 0;i < monster_amount;i++) {
		file >> Monster_name;//忘記加
		for (int j = 0;j < mon_db_amount;j++) {
			if (Monster_name == monster_db[j].name) {
				int two, three,four;
				monster_output[i] = monster_db[j];
				monster_output[i].code = code;
				code++;
				file >> monster_output[i].position.x >> monster_output[i].position.y;
				file >> two >> three >> four;
				switch (character_amount)
				{
				case 2:monster_output[i].switch_status(two);break;
				case 3:monster_output[i].switch_status(three);break;
				case 4:monster_output[i].switch_status(four);break;
				default:break;
				}
			}
		}
	}
	file.close();
}

TXT::~TXT(){//銷毀資料庫
	mydelete(character_db);
	mydelete(monster_db);
	mydelete_single(map);
}
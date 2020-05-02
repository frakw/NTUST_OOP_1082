#ifndef CREATURE_H
#define CREATURE_H

#include"Diary.h"
vector<day_log> Diary::day;
typedef struct {
	string name;
	int amount = 0;
}body_parts;

bool compare_string(body_parts a, body_parts b) {
	return a.name < b.name;
}

class Creature {
public:
	Creature() { name = ""; }
	Creature(string in_name);//Contains a creature named name.
	Creature(string in_name, Creature base);//A creature that contains the same information as the base of each body part.
	Creature& operator[](string in);
	Creature& operator=(int input);
	Creature& operator+=(int input);
	Creature& operator-=(int input);
	int operator+(int input);
	int operator-(int input);
	void PrintStatus();
	void PrintLog();
private:
	int index = 0;
	string name;
	int start_day_index;
	vector<body_parts> body;
};
//vector<day_log> Diary::day;

#endif
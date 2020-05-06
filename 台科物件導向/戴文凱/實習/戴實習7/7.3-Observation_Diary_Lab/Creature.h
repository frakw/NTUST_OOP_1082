#ifndef CREATURE_H
#define CREATURE_H

#include"Diary.h"
typedef struct {
	string name;
	int amount = 0;
}body_parts;

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

#endif
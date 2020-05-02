#ifndef DIARY_H
#define DIARY_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct {
	string name;
	string content;
}event;

typedef struct{
	string name;
	vector<event> event_list;
}day_log;
class Diary{
public:
	static void NewDay(string input) {
		day_log new_day;
		new_day.name = input;
		day.push_back(new_day);
	}
	static void NewEvent(string creature_name, string input) {
		event new_event;
		new_event.name = creature_name;
		new_event.content = input;
		day[day.size() - 1].event_list.push_back(new_event);
	}
	static vector<day_log> day;
};


#endif
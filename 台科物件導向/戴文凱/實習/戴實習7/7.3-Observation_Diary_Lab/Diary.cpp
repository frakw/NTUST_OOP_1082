#include"Diary.h"

void Diary::NewDay(string input) {
	day_log new_day;
	new_day.name = input;
	day.push_back(new_day);
}

void Diary::NewEvent(string creature_name, string input) {
	event new_event;
	new_event.name = creature_name;
	new_event.content = input;
	day[day.size() - 1].event_list.push_back(new_event);
}
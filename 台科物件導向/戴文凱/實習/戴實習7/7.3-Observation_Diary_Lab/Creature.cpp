#include "Creature.h"

vector<day_log> Diary::day;

bool compare_string(body_parts a, body_parts b) {
	return a.name < b.name;
}

Creature::Creature(string in_name) {//Contains a creature named name.
	name = in_name;
	start_day_index = Diary::day.size() - 1;
}
Creature::Creature(string in_name, Creature base) {//A creature that contains the same information as the base of each body part.
	name = in_name;
	body = base.body;
	start_day_index = Diary::day.size() - 1;
}
Creature& Creature::operator[](string in) {
	for (unsigned int i = 0;i < body.size();i++) {
		if (in == body[i].name) {
			index = i;
			return *this;
		}
	}
	index = body.size();
	body_parts new_part;
	new_part.name = in;
	new_part.amount = 0;
	//body.push_back({in,0});//不可以用C的寫法!!!!!!，不然會未定義參考到
	body.push_back(new_part);
	return *this;
}
Creature& Creature::operator=(int input) {
	string output = "'s " + body[index].name;
	if (!body[index].amount && input) {
		output = output + " appeared (";
	}
	else if (input == 0 && body[index].amount == 0) {//特別! 0變0不用輸出
		return *this;
	}
	else if (!input) {
		output = output + " disappeared (";
	}
	else if (input > body[index].amount) {
		output = output + " increased (";
	}
	else if (input < body[index].amount) {
		output = output + " decreased (";
	}
	else {
		return *this;
	}
	output = output + to_string(body[index].amount) + " -> ";
	body[index].amount = input;
	output = output + to_string(body[index].amount) + ").";
	Diary::NewEvent(name, output);
	return *this;
}
Creature& Creature::operator+=(int input) {
	return ((*this) = ((*this) + input));
}
Creature& Creature::operator-=(int input) {
	return ((*this) = ((*this) - input));
}
int Creature::operator+(int input) {
	return body[index].amount + input;
}

int Creature::operator-(int input) {
	return body[index].amount - input;
}
void Creature::PrintStatus() {

	sort(body.begin(), body.end(), compare_string);
	cout << name << "'s status:" << endl;
	for (int i = 0;i < body.size();i++) {
		if (body[i].amount != 0) {
			cout << body[i].name << " * " << body[i].amount << endl;
		}
	}
	cout << endl;
}
void Creature::PrintLog() {
	cout << name << "'s log:" << endl;
	for (int i = start_day_index;i < Diary::day.size();i++) {
		cout << "Day " << Diary::day[i].name << endl;
		for (int j = 0;j < Diary::day[i].event_list.size();j++) {
			if (Diary::day[i].event_list[j].name == name) {
				cout << name << Diary::day[i].event_list[j].content << endl;
			}
		}
	}
	cout << endl;
}
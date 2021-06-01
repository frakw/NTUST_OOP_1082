#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <utility>

using namespace std;

typedef pair<string, string> B_Info;
typedef map<B_Info, set<int>> Books;
Books database;

void insert(B_Info info, int edition) {
	if (database.count(info) && database[info].count(edition))
		cout << "Datum already exist." << endl;
	else {
		cout << "Insert " << info.second << "'s " << info.first << ", Edition: " << edition << "." << endl;
		database[info].insert(edition);
	}
}

void deleteEdition(B_Info info, int edition) {
	if (database.count(info) && database[info].count(edition)) {
		cout << "Delete " << info.second << "'s " << info.first << ", Edition: " << edition << "." << endl;
		database[info].erase(edition);
	}
	else
		cout << "Datum doesn't exist." << endl;
}

void deleteBook(B_Info info) {
	Books::iterator it = database.find(info);
	if (it != database.end()) {
		cout << "Delete " << info.second << "'s " << info.first << "." << endl;
		database.erase(it);
	}
	else
		cout << "Book doesn't exist." << endl;
}

void find(B_Info info) {
	if (database.count(info)) {
		set<int>::iterator it = database[info].begin();
		cout << "Title: " << info.first << "\tAuthor: " << info.second << "\tEdition:";
		for (; it != database[info].end(); it++) {
			if (it == database[info].begin())
				cout << " " << *it;
			else
				cout << ", " << *it;
		}
		cout << endl;
	}
	else
		cout << "Book doesn't exist." << endl;
}

void listAuthor(string author) {
	int count = 0;
	Books::iterator it = database.begin();
	for (; it != database.end(); it++) {
		if (it->first.second == author) {
			if (count == 0)
				cout << author << "'s Books: " << it->first.first;
			else
				cout << ", " << it->first.first;
			++count;
		}
	}
	if (!count)
		cout << "No book found.";
	cout << endl;
}


struct CmpByTitle {
	bool operator()(const B_Info& k1, const B_Info& k2) const {
		if (k1.first != k2.first)
			return k1.first < k2.first;
		else
			return k1.second < k2.second;
	}
};

struct CmpByAuthor {
	bool operator()(const B_Info& k1, const B_Info& k2) const {
		if (k1.second != k2.second)
			return k1.second < k2.second;
		else
			return k1.first < k2.first;
	}
};

void listByTitle() {
	map<B_Info, set<int>, CmpByTitle> tmp;
	Books::iterator it = database.begin();
	for (; it != database.end(); it++) {
		tmp[it->first] = it->second;
	}
	it = tmp.begin();
	for (; it != tmp.end(); it++) {
		cout << "Title: " << it->first.first << "\tAuthor: " << it->first.second << "\tEdition:";
		set<int>::iterator e_it = it->second.begin();
		for (; e_it != it->second.end(); e_it++) {
			if (e_it == it->second.begin())
				cout << " " << *e_it;
			else
				cout << ", " << *e_it;
		}
		cout << endl;
	}
}

void listByAuthor() {
	map<B_Info, set<int>, CmpByAuthor> tmp;
	Books::iterator it = database.begin();
	for (; it != database.end(); it++) {
		tmp[it->first] = it->second;
	}
	it = tmp.begin();
	for (; it != tmp.end(); it++) {
		cout << "Title: " << it->first.first << "\tAuthor: " << it->first.second << "\tEdition:";
		set<int>::iterator e_it = it->second.begin();
		for (; e_it != it->second.end(); e_it++) {
			if (e_it == it->second.begin())
				cout << " " << *e_it;
			else
				cout << ", " << *e_it;
		}
		cout << endl;
	}
}

int main() {
	string cmd;
	while (getline(cin, cmd)) {
		stringstream ss(cmd);
		getline(ss, cmd, '\"');
		if (cmd.substr(0, 6) == "Insert") {
			string title, author;
			int edition = -1;
			while (getline(ss, title, '\"')) {
				if (title != " ")
					break;
			}
			while (getline(ss, author, '\"')) {
				if (author != " ")
					break;
			}
			ss >> edition;
			B_Info b_info(title, author);
			if (title == "" || author == "" || edition == -1)
				cout << "Incomplete Command.";
			else
				insert(b_info, edition);
		}
		else if (cmd.substr(0, 14) == "Delete Edition") {
			string title, author;
			int edition = -1;
			while (getline(ss, title, '\"')) {
				if (title != " ")
					break;
			}
			while (getline(ss, author, '\"')) {
				if (author != " ")
					break;
			}
			ss >> edition;
			B_Info b_info(title, author);
			if (title == "" || author == "" || edition == -1)
				cout << "Incomplete Command.";
			else
				deleteEdition(b_info, edition);
		}
		else if (cmd.substr(0, 11) == "Delete Book") {
			string title, author;
			while (getline(ss, title, '\"')) {
				if (title != " ")
					break;
			}
			while (getline(ss, author, '\"')) {
				if (author != " ")
					break;
			}
			B_Info b_info(title, author);
			if (title == "" || author == "")
				cout << "Incomplete Command.";
			else
				deleteBook(b_info);
		}
		else if (cmd.substr(0, 9) == "Find Book") {
			string title, author;
			while (getline(ss, title, '\"')) {
				if (title != " ")
					break;
			}
			while (getline(ss, author, '\"')) {
				if (author != " ")
					break;
			}
			B_Info b_info(title, author);
			if (title == "" || author == "")
				cout << "Incomplete Command.";
			else
				find(b_info);
		}
		else if (cmd.substr(0, 11) == "Find Author") {
			string author;
			while (getline(ss, author, '\"')) {
				if (author != " ")
					break;
			}
			if (author == "")
				cout << "Incomplete Command.";
			else
				listAuthor(author);
		}
		else if (cmd.substr(0, 13) == "Sort by Title") {
			listByTitle();
		}
		else if (cmd.substr(0, 14) == "Sort by Author") {
			listByAuthor();
		}
		/*else if (cmd == "") {
			continue;
		}*/
		else {
			cout << "Unknown Command." << endl;
		}
	}
	return 0;
}
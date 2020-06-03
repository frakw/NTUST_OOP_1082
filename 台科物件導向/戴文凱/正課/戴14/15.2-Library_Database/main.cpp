#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
class Book {
public:
    Book() {}
    Book(string in_title,string in_author,string in_edition):title(in_title),author(in_author),edition(in_edition) {}
    void print() {
        
    }
    bool operator==(const Book& input) {
        return title == input.title && author == input.author && edition == input.edition;
    }
    string title;
    string author;
    string edition;
};
void read_title_author_edition(stringstream& ss, string& title, string& author, string& edition);
int find_in(vector<Book>& lib, Book);

class err{
public:
    err(int x) {
        switch (x)
        {
        case 0: out = "Unknown Command.";break;
        case 1: out = "Incomplete Command.";break;
        case 2: out = "Datum already exist.";break;
        case 3: out = "Book doesn't exist.";break;
        case 4: out = "No book found.";break;
        case 5: out = "Datum doesn't exist.";break;
        default:
            break;
        }
    }
    string out;
};

int main() {
    string line;
    vector<Book> library;
    while (getline(cin, line)) {
        stringstream ss(line);
        string command,command2;
        string title, author, edition;
        int index;
        ss >> command;
        try {
            if (command == "Insert") {
                read_title_author_edition(ss, title, author, edition);
                if (!title.length() || !author.length() || !edition.length()) throw err(1);
                if ((index=find_in(library, Book(title, author, edition))) == -1) {
                    library.push_back(Book(title, author, edition));
                    cout << "Insert " << library.back().author << "'s " << library.back().title << ", Edition: "<< library.back().edition << ".\n";
                }
                else {
                    throw err(2);
                }
            }
            else if (command == "Delete") {
                ss >> command2;
                read_title_author_edition(ss, title, author, edition);
                if (command2 == "Edition") {
                    if ((index = find_in(library, Book(title, author, edition))) == -1) {
                        throw err(5);
                    }
                    library.erase(library.begin()+index);
                    cout << "Delete " << author << "'s " << title << ", Edition: " << edition << ".\n";
                }
                else if (command2 == "Book") {
                    bool find = false;
                    for (int i = 0;i < library.size();i++) {
                        if (library[i].title == title && library[i].author == author) {
                            library.erase(library.begin() + i);
                            find = true;
                        }
                    }
                    if (!find) throw err(3);
                    cout << "Delete "<< author<<"'s "<< title << ".\n";
                }
                else {
                    throw err(0);
                }
            }
            else if (command == "Find") {
                ss >> command2;
                read_title_author_edition(ss, title, author, edition);
                if (command2 == "Book") {
                    set<int> result;
                    for (int i = 0;i < library.size();i++) {
                        if (library[i].title == title && library[i].author == author) {
                            result.insert(atoi(library[i].edition.c_str()));
                        }
                    }                 
                    if (!result.size()) throw err(3);
                    cout << "Title: " << title << "\tAuthor: " << author << "\tEdition: ";
                    int tmp = 0;
                    for (auto i = result.begin();i != result.end();i++) {
                        cout << (tmp != 0 ? ", " : "") << *i;
                        tmp++;
                    }
                    cout << endl;
                }
                else if (command2 == "Author") {//此處的title是author
                    set<string> result;
                    for (int i = 0;i < library.size();i++) {
                        if (library[i].author == title) {
                            result.insert(library[i].title);
                        }
                    }
                    if (!result.size()) throw err(4);
                    cout << title << "'s Books: ";
                    int tmp = 0;
                    for (auto i = result.begin();i != result.end();i++) {
                        cout << (tmp != 0 ? ", " : "") << *i;
                        tmp++;
                    }
                    cout << endl;
                }
                else {
                    throw err(0);
                }
            }
            else if (command == "Sort") {
                string by, command3;
                ss >> by >> command3;
                if (command3 == "Title") {
                    sort(library.begin(), library.end(),
                        [&](Book a,Book b)->bool{
                            if (a.title == b.title) {
                                if (a.author == b.author) {
                                    return stoi(a.edition) < stoi(b.edition);
                                }
                                return a.author < b.author;
                            }
                            return a.title < b.title;
                        });

                    for (int i = 0;i < library.size();i++) {
                        int next= i + 1;
                        cout << "Title: " << library[i].title << "\tAuthor: " << library[i].author << "\tEdition: "<< library[i].edition;
                        while (next < library.size()) {
                            if (library[i].title == library[next].title && library[i].author == library[next].author) {
                                cout <<", "<< library[next].edition;
                            }
                            else {
                                break;
                            }
                            next++;
                        }
                        cout << endl;
                        i = next - 1;
                    }
                }
                else if (command3 == "Author") {
                    sort(library.begin(), library.end(),
                        [&](Book a, Book b)->bool {
                            if (a.author == b.author) {
                                if (a.title == b.title) {
                                    return atoi(a.edition.c_str()) < atoi(b.edition.c_str());
                                }
                                return a.title < b.title;
                            }
                            return a.author < b.author;
                        });

                    for (int i = 0;i < library.size();i++) {
                        int next = i;
                        cout << "Title: " << library[i].title << "\tAuthor: " << library[i].author << "\tEdition: " << library[i].edition;
                        while (next < library.size()) {
                            next++;
                            if (library[i].title == library[next].title && library[i].author == library[next].author) {
                                cout << ", " << library[next].edition;
                            }
                            else {
                                break;
                            }
                        }
                        cout << endl;
                        i = next - 1;
                    }
                }
                else {
                    throw err(0);
                }
            }
            else {
                throw err(0);
            }
        }
        catch (err x) {
            cout << x.out << endl;
        }
    }
    return 0;
}


void read_title_author_edition(stringstream& ss, string& title, string& author, string& edition) {
    string others;
    getline(ss, others);
    int quotation_count = 0;
    for (int i = 0;i < others.length();i++) {
        if (others[i] == '"') {
            quotation_count++;
        }
        else if (quotation_count < 2 && quotation_count>0) {
            title.push_back(others[i]);
        }
        else if (quotation_count < 4 && quotation_count>2) {
            author.push_back(others[i]);
        }
        else if (others[i] == ' ' || others[i] == '\n' || others[i] == 13) {

        }
        else if (quotation_count >= 4) {
            edition.push_back(others[i]);
        }
    }
}

int find_in(vector<Book>& lib,Book check) {
    for (int i = 0;i < lib.size();i++) {
        if (lib[i] == check) {
            return i;
        }
    }
    return -1;
}
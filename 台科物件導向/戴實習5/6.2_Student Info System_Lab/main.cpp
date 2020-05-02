#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
class student {
public:
    string id;
    string name;
    string gender;
    string height;
    string weight;
    void print() {
        cout << id << '\t' << name << '\t' << gender << '\t' << height << '\t' << weight << endl;
    }
};
bool compare_id(student, student);
int find_student_pos(vector<student>, string);
int main() {
    string input;
    vector<student> all_data;
    while (getline(cin, input)) {
        student data;
        string command;
        stringstream in(input);
        int index;
        in >> command;
        if (command == "Add") {
            in >> data.id >> data.name >> data.gender >> data.height >> data.weight;
            int i = 0;
            for (i = 0;i < all_data.size();i++) {
                if (data.id == all_data[i].id) {
                    cout << "The student's ID is duplicate." << endl;
                    goto loop_end;
                }
            }
            all_data.push_back(data);
        }
        else if (command == "Edit") {
            string variable_name;
            in >> data.id >> variable_name;
            if ((index = find_student_pos(all_data,data.id))==-1) {//檢查學生是否存在
                goto loop_end;
            }
            if (variable_name == "Name") {
                in >> all_data[index].name;
            }
            else if (variable_name == "Gender") {
                in >> all_data[index].gender;
            }
            else if (variable_name == "Height") {
                in >> all_data[index].height;
            }
            else if (variable_name == "Weight") {
                in >> all_data[index].weight;
            }
        }
        else if (command == "Del") {
            in >> data.id;
            if ((index = find_student_pos(all_data, data.id)) == -1) {//檢查學生是否存在
                goto loop_end;
            }
            all_data.erase(all_data.begin()+index);
        }
        else if (command == "Find") {
            in >> data.id;
            if ((index = find_student_pos(all_data, data.id)) == -1) {//檢查學生是否存在
                goto loop_end;
            }
            all_data[index].print();
        }
        else if (command == "List") {
            sort(all_data.begin(), all_data.end(),compare_id);
            for (int i = 0;i < all_data.size();i++) {
                all_data[i].print();
            }
        }
    loop_end:;
    }
    return 0;
}

bool compare_id(student a,student b) {
    return a.id < b.id;
}

int find_student_pos(vector<student> all_data,string id) {
    int index = -1;
    for (int i = 0;i < all_data.size();i++) {
        if (id == all_data[i].id) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "Student Not Found." << endl;
    }
    return index;
}
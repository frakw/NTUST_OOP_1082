#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class student {
public:
    string id;
    bool deny=false;
    string symptom;
    string travel;
    void print() {
        cout << id << '\t' << symptom << '\t' << travel << '\t' << (deny ? "Denied" : "Allowed") << endl;
    }
};
int main() {
    string input;
    vector<student> all_data;
    const string deny_symptom[5] = { "Fever","Dry cough","Fatigue","Shortness of breath","Chills" };
    const string deny_travel[9] = { "China" ,"USA" ,"Italy" ,"Spain" ,"Germany" ,"Iran" ,"France" ,"UK" ,"Switzerland" };
    
    while (getline(cin, input)) {
        if (input == "List") {
            for (int i = 0;i < all_data.size();i++) {
                all_data[i].print();
            }
            continue;
        }
        stringstream in(input);
        student data;
        string process,trash;
        string temp;
        char space;
        int travel_pos=0;
        in >> trash >> data.id;
        getline(in, process);
        for (int i = 0;i < process.length();i++) {//找出最後一個空白的位置
            if (process[i] == ' ') {
                travel_pos = i+1;
            }
        }
        for (int i = 1;i < travel_pos-1;i++) {//最後一個空白前就是症狀，丟入data
            data.symptom.push_back(process[i]);
        }
        for (int i = travel_pos;i < process.length();i++) {//最後一個空白後就是旅遊史，丟入data
            data.travel.push_back(process[i]);
        }
        for (int i = 0;i < 5;i++) {//檢查症狀
            if (data.symptom == deny_symptom[i]) {
                data.deny = true;
            }
        }
        for (int i = 0;i < 9;i++) {//檢查旅遊史
            if (data.travel == deny_travel[i]) {
                data.deny = true;
            }
        }
        all_data.push_back(data);//丟入all_data
        cout << data.id << " Access " << (data.deny ? "denied." : "allowed.") << endl;
        input.clear();
    }
    return 0;
}
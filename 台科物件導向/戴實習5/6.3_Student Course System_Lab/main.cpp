#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
char week[5] = {'M','T','W','R','F'};
class Course;
class Time;
class Time {
public:
    char day;
    int time;
};
class Course {
public:
    string name;
    vector<Time> time;
    void print() {
        cout << name;
        for (int i = 0;i < 5;i++) {//修正錯誤: 對:ComputerGraphics T10 R1 R9 | 錯:ComputerGraphics R1 R9 T10
            for (int j = 1;j < 11;j++) {
                for (int k = 0;k < time.size();k++) {
                    if (time[k].day == week[i] && time[k].time == j) {
                        cout << ' ' << time[k].day << time[k].time;
                    }
                }
            }
        }
        /*原來的錯誤
        for (int i = 0;i < time.size();i++) {
            cout << ' ' << time[i].day << time[i].time;
        }
        */
        cout << endl;
    }
};

class student {
public:
    string name;
    vector<Course> course;
    void print() {
        for (int i = 0;i < 5;i++) {
            cout << week[i]<<":";
            for (int x = 1;x < 11;x++) {
                for (int j = 0;j < course.size();j++) {
                    for (int k = 0;k < course[j].time.size();k++) {
                        if (course[j].time[k].time == x && course[j].time[k].day==week[i]) {
                            cout << ' ' << x << ':' << course[j].name;
                        }
                    }
                }
            }
            cout << endl;
        }
    }
private:
};
int find_student_pos(vector<student>, string);
int main() {
    string input;//整行字串
    vector<student> all_data;//所有學生資料
    while (getline(cin, input)) {
        stringstream in(input);
        string command;//指令
        student data;//push_back與暫存資料用
        int index;
        in >> command;
        if (command == "AddStudent") {
            in >> data.name;
            for (int i = 0;i < all_data.size();i++) {//檢查有無重覆
                if (all_data[i].name == data.name) {
                    cout << "The student's name is duplicate." << endl;
                    goto loop_end;
                }
            }
            all_data.push_back(data);
        }
        else if (command == "AddCourse") {
            Course course;//用來push_back
            Time time;//用來push_back
            string others;//存課程時間的字串，經處理後存入vector: W1 W2 W3
            in >> data.name >> course.name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//檢查學生是否存在
                goto loop_end;
            }
            getline(in, others);
            for (int i = 0;i < others.length();i++) {//刪空白
                if (others[i] == ' ') {
                    others.erase(others.begin()+i);
                    i--;//刪除空白後，不用++，用--抵銷，留在原地就好
                }
            }
            stringstream in2(others);
            while(in2>>time.day){//衝突課堂檢查
                in2 >> time.time;
                for (int j = 0;j < all_data[index].course.size();j++) {
                    for (int k = 0;k < all_data[index].course[j].time.size();k++) {
                        if (all_data[index].course[j].time[k].day == time.day && all_data[index].course[j].time[k].time == time.time) {
                            cout << "Course conflict." << endl;
                            goto loop_end;
                        }
                    }
                }
                course.time.push_back(time);
            }
            
            all_data[index].course.push_back(course);
        }
        else if (command == "DelStudent") {
            in >> data.name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//檢查學生是否存在
                goto loop_end;
            }
            all_data.erase(all_data.begin()+index);
        }
        else if (command == "DelCourse") {
            in >> data.name;
            string course_name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//檢查學生是否存在
                goto loop_end;
            }
            in >> course_name;
            int index2=-1;//存課堂的編號
            for (int i = 0;i < all_data[index].course.size();i++) {//檢查課堂存不存在
                if (course_name == all_data[index].course[i].name) {
                    index2 = i;
                }
            }
            if (index2 == -1) {
                cout << "The course does not exist." << endl;
                continue;
            }
            all_data[index].course.erase(all_data[index].course.begin()+index2);
        }
        else if (command == "Print") {
            in >> data.name;
            string temp;//存課程名字
            if (data.name == "StudentList") {
                if (all_data.size() == 0) {
                    cout << "The Students list is empty." << endl;
                    continue;
                }
                for (int i = 0;i < all_data.size();i++) {
                    cout << all_data[i].name<<endl;
                }
                continue;
            }
            int index = -1;//存學生的編號
            for (int i = 0;i < all_data.size();i++) {//檢查學生存不存在
                if (all_data[i].name == data.name) {
                    index = i;
                }
            }
            if (index == -1) {
                cout << "The student's name does not exist." << endl;
                continue;
            }
            else if (in >> temp) {//如果有指定列印哪個課程:Print Mike English
                int i;
                for (i = 0;i < all_data[index].course.size();i++) {//檢查課程存不存在
                    if (temp== all_data[index].course[i].name) {
                        all_data[index].course[i].print();
                        break;
                    }
                }
                if (i == all_data[index].course.size()) {
                    cout << "The course does not exist." << endl;
                }
            }
            else {//沒有指定列印哪個課程，印出課表:Print English
                all_data[index].print();
            }
        }
    loop_end:;
    }
    return 0;
}

int find_student_pos(vector<student> all_data, string name) {
    int index = -1;
    for (int i = 0;i < all_data.size();i++) {
        if (name == all_data[i].name) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "The student's name does not exist." << endl;
    }
    return index;
}


int find_course_pos(student x, string course_name) {
    int index = -1;
    for (int i = 0;i < x.course.size();i++) {
        if (course_name == x.course[i].name) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "The student's name does not exist." << endl;
    }
    return index;
}
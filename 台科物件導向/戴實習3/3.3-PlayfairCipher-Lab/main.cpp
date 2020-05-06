#define mycode
#ifdef mycode
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class coord {
public:
    int x;
    int y;
};
int main() {
    string message,key;
    while (getline(cin, message)) {
        getline(cin, key);
        char matrix[5][5] = { 0 };
        bool alpha_showed[26] = { 0 };//存字母是否出現
        int matrix_count = 0;
        for (int i = 0;i < key.length();i++) {//j取代為i
            if (key[i] == 'j') { key[i] = 'i'; }
        }
        for (int i = 0;i < key.length();i++) {//字串填入5*5方格
            if (!alpha_showed[key[i]-'a']) {
                alpha_showed[key[i]-'a'] = true;
                matrix[matrix_count / 5][matrix_count % 5] = key[i];
                matrix_count++;
            }
        }
        for (int i = 0;i < 26;i++) {//剩餘方格補未出現字母，從a~z
            if (i == 9) {// j時不做
                continue;
            }
            if (!alpha_showed[i]) {
                alpha_showed[i] = true;
                matrix[matrix_count / 5][matrix_count % 5] = i + 'a';
                matrix_count++;
            }
        }
        vector<char> result;
        for (int i = 0;i < message.length();i++) {
            result.push_back(message[i]);
        }
        int gg=0;
        while ((gg + 1) < result.size()) {
            if (result[gg] == result[gg + 1]) {
                result.insert(result.begin() + gg + 1, 'x');
            }
            gg += 2;
            /*曾經的錯誤
            if (result[gg] == result[gg + 1]) {
                result.insert(result.begin() + gg + 1, 'x');
                gg++;
            }
            else {
                gg += 2;
            }
            */
        }
        if (result.size() % 2) {
            result.insert(result.end(), 'x');
        }
        for (int i = 0;i < result.size();i += 2) {
            coord a = {0,0}, b = { 0,0 };
            for (int j = 0;j < 5;j++) {
                for (int k = 0;k < 5;k++) {
                    if (result[i] == matrix[j][k]) {
                        a.x = k;
                        a.y = j;
                    }
                    if (result[i+1] == matrix[j][k]) {
                        b.x = k;
                        b.y = j;
                    }
                }
            }
            if (a.x == b.x) {
                 cout << matrix[(a.y+1) % 5][a.x];
                 cout << matrix[(b.y + 1) % 5][b.x];
            }
            else if (a.y == b.y) {
                  cout << matrix[a.y][(a.x+1)%5];
                  cout << matrix[b.y][(b.x+1)%5];
            }
            else {
                cout << matrix[a.y][b.x] << matrix[b.y][a.x];
            }
        }
        cout << endl;
    }
    return 0;
}
#endif
#ifndef mycode
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Point
{
    int row = 0, column = 0;
};

int main() {
    string message;


    while (cin >> message)
    {
        string keyword;
        vector<string> split;

        char same_array[25] = { ' ' };
        int same_count = 0;
        char keyTable[5][5];
        int row = 0;
        int column = 0;
        bool have_same = false;
        bool have_ij = false;
        cin >> keyword;
        split.clear();
        row = 0;
        column = 0;
        same_count = 0;
        have_ij = false;

        // 刪除相同者              
        for (int i = 0; i < keyword.length(); i++)
        {
            have_same = false;
            for (int j = 0; j < same_count; j++)
            {
                if (same_array[j] == keyword[i])
                    have_same = true;
                if ((keyword[i] == 'i' || keyword[i] == 'j') && have_ij)
                    have_same = true;
            }
            if (!have_same)
            {
                if (keyword[i] == 'i' || keyword[i] == 'j')
                    have_ij = true;

                if (column > 4)
                {
                    column = 0;
                    row += 1;
                    if (keyword[i] == 'j')
                        keyword[i] = 'i';
                    keyTable[row][column] = keyword[i];
                    same_array[same_count] = keyword[i];
                    same_count += 1;
                    column += 1;
                }
                else
                {
                    if (keyword[i] == 'j')
                        keyword[i] = 'i';
                    keyTable[row][column] = keyword[i];
                    column += 1;
                    same_array[same_count] = keyword[i];
                    same_count += 1;
                }
            }
        }

        // 剩餘補入        
        for (int i = 0; i < 26; i++)
        {
            have_same = false;
            for (int j = 0; j < same_count; j++)
            {
                if (same_array[j] == 'a' + i)
                    have_same = true;
                if (('a' + i == 'i' || 'a' + i == 'j') && have_ij)
                    have_same = true;
            }
            if (!have_same)
            {
                if ('a' + i == 'i' || 'a' + i == 'j')
                    have_ij = true;

                if (column > 4)
                {
                    column = 0;
                    row += 1;
                    keyTable[row][column] = 'a' + i;
                    if (keyTable[row][column] == 'j')
                        keyTable[row][column] = 'i';
                    column += 1;
                }
                else
                {
                    keyTable[row][column] = 'a' + i;
                    if (keyTable[row][column] == 'j')
                        keyTable[row][column] = 'i';
                    column += 1;
                }
            }
        }

        string part = "";
        int push = 0;
        for (int i = 0; i < message.length(); i += 2)
        {
            if (i == message.length() - 2 && (push == 1))
            {
                part += message[i - push];
                part += message[i + 1 - push];
                split.push_back(part);
                part.clear();
                part += message[i + 2 - push];
                part += 'x';
                split.push_back(part);
                part.clear();
                break;
            }

            if (message[i - push] == message[i + 1 - push])
            {
                part += message[i - push];
                part += 'x';
                push += 1;
                split.push_back(part);
                part.clear();
            }
            else
            {
                part += message[i - push];
                if (i == message.length() - 1 - push)
                    part += 'x';
                else
                    part += message[i + 1 - push];
                split.push_back(part);
                part.clear();
            }
        }



        Point one, two;
        for (int i = 0; i < split.size(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (keyTable[j][k] == split[i][0])
                    {
                        one.row = j;
                        one.column = k;
                    }
                    if (keyTable[j][k] == split[i][1])
                    {
                        two.row = j;
                        two.column = k;
                    }
                }
            }

            if (one.row == two.row)
            {
                if (one.column + 1 > 4)
                    one.column = -1;
                if (two.column + 1 > 4)
                    two.column = -1;
                split[i].clear();
                split[i] += keyTable[one.row][one.column + 1];
                split[i] += keyTable[two.row][two.column + 1];
            }
            else if (one.column == two.column)
            {
                if (one.row + 1 > 4)
                    one.row = -1;
                if (two.row + 1 > 4)
                    two.row = -1;
                split[i].clear();
                split[i] += keyTable[one.row + 1][one.column];
                split[i] += keyTable[two.row + 1][two.column];
            }
            else
            {
                split[i].clear();
                split[i] += keyTable[one.row][two.column];
                split[i] += keyTable[two.row][one.column];
            }

            for (int j = 0; j < split[i].length(); j++)
            {
                if (split[i][j] <= 'z' && split[i][j] >= 'a')
                    cout << split[i][j];
            }
        }
        cout << endl;
    }
}
#endif
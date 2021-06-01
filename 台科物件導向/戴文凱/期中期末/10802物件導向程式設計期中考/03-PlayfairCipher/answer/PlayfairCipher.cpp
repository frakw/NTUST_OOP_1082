// Project : Playfair Cipher
// Create : Pin-Shao Chen
// Date : 20200308
// E-mail : fansen7@gmail.com

#include<iostream>
#include<string>
#include<vector>

using namespace std;

string playfairKeyGen(string key) {
	int alphaCheck[26];
	for (int i = 0; i < 26; i++) alphaCheck[i] = 0;
	string tempKey = "";

	for (int i = 0; i < key.size(); i++) { //check 重複，建tempkey
		int index = key[i] - 'a';
		if (alphaCheck[index] > 0) continue;
		tempKey += key[i];
		alphaCheck[index]++;
	}
	for (int i = 0; i < 26; i++) {
		if (!alphaCheck[i])
			tempKey += i + 'a';
	}
	int indexI = tempKey.find('i'),
		indexJ = tempKey.find('j');

	if (indexI > indexJ) //把j拿掉
	{ // J在I前
		tempKey.erase(indexI, 1);
		tempKey[indexJ] = 'i';
	}
	else { //I在J前
		tempKey.erase(indexJ, 1);
	}

	return tempKey;
}

string playfairCipher(string key, string plainText) {

	vector<vector<char>> playfairTable;
	string cipherText = "";
	for (int i = 0; i < 5; i++) playfairTable.push_back(vector<char>());

	for (int i = 0; i < plainText.size(); i++) {
		if (plainText[i] == 'j')
			plainText[i] = 'i';
	}
	key = playfairKeyGen(key);
	//cout << endl;
	//cout << "Playfair Table:" << endl;
	for (int i = 0; i < 5; i++) { // 建palyfair table
		for (int j = 0; j < 5; j++) {
			playfairTable[i].push_back(key[i * 5 + j]);
		//	cout << key[i * 5 + j];
		}
		//cout << endl;
	}
	//cout << endl;
	for (int i = 0; i < plainText.size(); i += 2) { //兩兩分組
		if (plainText[i] == plainText[i + 1]) {
			plainText.insert(i + 1, "x");
		}
	}
	if (plainText.size() % 2) plainText += "x"; //補到偶數位

	for (int i = 0; i < plainText.size(); i += 2) {
		char c1 = plainText[i], c2 = plainText[i + 1];
		int c1_row = key.find(c1) / 5,
			c1_col = key.find(c1) % 5,
			c2_row = key.find(c2) / 5,
			c2_col = key.find(c2) % 5;

		if ((c1_row == c2_row) && (c1_col != c2_col)) { //同一列
			if (c1_col == 4) {//邊緣
				cipherText.push_back(playfairTable[c1_row][c1_col + 1 - 5]);
			}
			else {
				cipherText.push_back(playfairTable[c1_row][c1_col + 1]);
			}
			if (c2_col == 4) { //邊緣
				cipherText.push_back(playfairTable[c2_row][c2_col + 1 - 5]);
			}
			else {
				cipherText.push_back(playfairTable[c2_row][c2_col + 1]);
			}
		}
		else if ((c1_row != c2_row) && (c1_col == c2_col)) { //同一行
			if (c1_row == 4) {//邊緣
				cipherText.push_back(playfairTable[c1_row + 1 - 5][c1_col]);
			}
			else {
				cipherText.push_back(playfairTable[c1_row + 1][c1_col]);
			}
			if (c2_row == 4) { //邊緣
				cipherText.push_back(playfairTable[c2_row + 1 - 5][c2_col]);
			}
			else {
				cipherText.push_back(playfairTable[c2_row + 1][c2_col]);
			}
		}
		else {
			cipherText.push_back(playfairTable[c1_row][c2_col]);
			cipherText.push_back(playfairTable[c2_row][c1_col]);
		}
	}
	return cipherText;
}

int main() {
	string plainText = "";
	string key = "";

	while (cin >> plainText) {
		cin >> key;
		cout << playfairCipher(key, plainText) << endl;
	}
	return 0;
}
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string ranks = "A234567891JQKA";
string suits = "CDHS";

class CMAP {
private:
	int cnt;
	vector<vector<bool>> cards;
	vector<int> rank_cnt;
	vector<int> suit_cnt;
public:
	vector<vector<string>> errlog;
	CMAP() {
		cards.resize(4, vector<bool>(14, false));
		rank_cnt.resize(14, 0);
		suit_cnt.resize(4, 0);
		errlog.resize(3);
	}
	vector<int> parse_card(string sc, int offset = 0) {
		vector<int> card(2, -1);
		card[1] = distance(find(ranks.rbegin() + offset, ranks.rend(), sc[1]), ranks.rend()) - 1;
		card[0] = distance(find(suits.rbegin(), suits.rend(), sc[0]), suits.rend()) - 1;
		return card;
	}
	bool put_card(string sc) {
		vector<int> c = parse_card(sc);
		if (c[0] == -1 || c[1] == -1) {
			string errmsg;
			errmsg += sc;
			errmsg += " does not exist";
			errlog[1].push_back(errmsg);
			return false;
		}
		if (cards[c[0]][c[1]]) {
			string errmsg;
			errmsg += sc;
			errmsg += " is the same";
			errlog[2].push_back(errmsg);
			return false;
		}
		cards[c[0]][c[1]] = true;
		suit_cnt[c[0]]++;
		rank_cnt[c[1]]++;
		if (sc[1] == 'A') {
			vector<int> c = parse_card(sc, 1);
			cards[c[0]][c[1]] = true;
			suit_cnt[c[0]]++;
			rank_cnt[c[1]]++;
		}
		return true;
	}
	void load_string(string src, int pos) {
		istringstream iss(src);
		string sc;
		int cnt = 0;

		while (iss >> sc) {
			cnt++;
			put_card(sc);
		}

		if (cnt != 13) {
			string errmsg;
			errmsg += "The number of the card in the ";
			errmsg += to_string(pos);
			errmsg += "-th set is ";
			errmsg += to_string(cnt);
			errlog[0].push_back(errmsg);
		}

	}

	void search_max() {
		// for each row to get same-suit straight
		for (int s = 3; s >= 0; s--) {
			for (int r = 13; r >= 4; r--) {
				int cnt = 0;
				for (int k = 0; k < 5; k++)
					if (cards[s][r - k]) cnt++;

				if (cnt == 5) {
					for (int k = 4; k >= 0; k--) {
						if (k != 4) cout << " ";
						cout << suits[s] << ranks[r - k];
						if (ranks[r - k] == '1') cout << '0';
					}
					cout << endl;
					return;
				}
			}
		}

		// basic straight
		for (int r = 13; r >= 4; r--) {
			int cnt = 0;
			for (int k = 0; k < 5; k++)
				if (rank_cnt[r - k] > 0) cnt++;

			if (cnt == 5) {
				for (int k = 4; k >= 0; k--) {
					if (k != 4) cout << " ";

					for (int s = 3; s >= 0; s--) {
						if (cards[s][r - k]) {
							cout << suits[s] << ranks[r - k];
							if (ranks[r - k] == '1') cout << '0';
							break;
						}
					}
				}
				cout << endl;
				return;
			}
		}
	}
};

int main() {
	int n;
	vector<string> raws;
	string src;

	cin >> n;
	cin.get();
	while (getline(cin, src)) {
		if (src.size() == 0) continue;
		raws.push_back(src);
	}
	int raws_size = raws.size();
	if (raws_size > n)
		cout << "The number of the set is not in the range of (0, " << n << ")" << endl;
	else if (raws_size < n)
		cout << "The number of the line is less than " << n << endl;
	n = min(n, raws_size);

	vector<CMAP> cs;
	for (int i = 0; i < n; i++) {
		CMAP c;
		c.load_string(raws[i], i + 1);
		cs.push_back(c);
		for (string errmsg : c.errlog[0])
			cout << errmsg << endl;
	}
	for (auto c : cs) {
		for (string errmsg : c.errlog[1])
			cout << errmsg << endl;
		for (string errmsg : c.errlog[2])
			cout << errmsg << endl;
		c.search_max();
	}
	return 0;
}
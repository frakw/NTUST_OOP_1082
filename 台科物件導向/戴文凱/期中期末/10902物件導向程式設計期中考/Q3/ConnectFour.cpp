#include <iostream>

class ConnectFour {
	int board[7][6];
	int turn;
	int checker;
public:
	ConnectFour() {
		Reset();
	}
	
	void Reset() {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				board[i][j] = 0;
			}
		}
		checker = 1;
		turn = 0;
	}

	void Place(int idx) {
		if (idx > 6 || idx < 0) {
			std::cout << "The line isn't exist, choose again:" << std::endl;
			return;
		}
		int pos = -1;
		for (int i = 0; i < 6; i++) {
			if (board[idx][i] == 0) {
				pos = i;
				break;
			}
		}
		if (pos == -1) {
			std::cout << "The line is full, choose again:" << std::endl;
		}
		else {
			board[idx][pos] = checker;
			turn += 1;
			if (checkWin(idx, pos)) {
				if (checker == 1) {
					std::cout << "YELLOW wins!" << std::endl;
				}
				else {
					std::cout << "RED wins!" << std::endl;
				}
				Reset();
			}
			else if(turn == 42){
				std::cout << "Draw!" << std::endl;
				Reset();
			}
			else {
				checker = (checker == 1 ? 2 : 1);
			}
		}
	}

	bool checkWin(int idx, int pos) {
			int count = 1;
			// check diagonally
			for (int i = idx + 1, j = pos + 1; i < 7 && j < 6 && (board[idx][pos] == board[i][j]); i++, j++)
				count += 1;
			for (int i = idx - 1, j =  pos - 1; i >= 0 && j >= 0 && (board[idx][pos] == board[i][j]); i--, j--)
				count += 1;
			if (count >= 4)
				return true;
			count = 1;

			// check diagonally
			for (int i = idx + 1, j = pos - 1; i < 7 && j >= 0 && (board[idx][pos] == board[i][j]); i++, j--)
				count += 1;
			for (int i = idx - 1, j = pos + 1; i >= 0 && j < 6 && (board[idx][pos] == board[i][j]); i--, j++)
				count += 1;
			if (count >= 4)
				return true;
			count = 1;

			// check vertically
			for (int i = idx + 1; i < 7 && (board[idx][pos] == board[i][pos]); i++)
				count += 1;
			for (int i = idx - 1; i >= 0 && (board[idx][pos] == board[i][pos]); i--)
				count += 1;
			if (count >= 4)
				return true;
			count = 1;

			// check horizontally
			for (int j = pos + 1; j < 6 && (board[idx][pos] == board[idx][j]); j++)
				count += 1;
			for (int j = pos - 1; j >= 0 && (board[idx][pos] == board[idx][j]); j--)
				count += 1;
			if (count >= 4)
				return true;

			return false;
	}
};

int main(){
	ConnectFour c4;

	int idx;
	while (std::cin >> idx) {
		c4.Place(idx-1);
	}

	return 0;
}
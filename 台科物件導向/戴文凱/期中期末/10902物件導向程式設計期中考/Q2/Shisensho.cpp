#include <iostream>
#include <stack>

// shisensho game manager
class Shisensho {
	// store traverse state of this path.
	struct state {
		int x = 0; // position x
		int y = 0; // position y
		int turn = 0; // turn counts
		int dir = 0; // direction
		int vIdx = 0; // visit index, it represents the temporal order of the state. 
					// If a visit index is larger than the value stores in "visit map", it means that this place is already visited.

		state(int _x = 0, int _y = 0, int _t = 0, int _d = 0, int _v = 0) : x(_x), y(_y), turn(_t), dir(_d), vIdx(_v)  {

		}
	};

public:
	int board[8][8]; // board
	int visit[8][8]; // visit

	// Constructor.
	// Initialize board informations.
	Shisensho() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j] = 0;
				visit[i][j] = 0;
			}
		}
	}

	// Read board information form standard input.
	void ReadBoardInput() {
		for (int i = 1; i < 7; i++) {
			for (int j = 1; j < 7; j++) {
				int symbol;
				std::cin >> symbol;
				board[i][j] = symbol;
			}
		}
	}

	// Return true if there exists a path that can match these two symbols on the board.
	bool Match(int x1, int y1, int x2, int y2) {
		// initialize visit map.
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				visit[i][j] = -1;
			}
		}

		// if the position is out of range.
		if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) {
			return false;
		}

		// if is the same position.
		if (x1 == x2 && y1 == y2) {
			return false;
		}

		// if symbol is empty or not match.
		if (board[y1][x1] == 0 || board[y1][x1] != board[y2][x2]) {
			return false;
		}
		
		// using stack to emulate traversal.
		std::stack<state> pathStack;

		// set starting point.
		pathStack.push(state(x1, y1, -1, -1));

		// directions to traverse.
		int directions[4][2] = { {1,0},{-1,0},{0,-1},{0,1} };

		while (!pathStack.empty())
		{
			// pop next traverse target.
			state s = pathStack.top();
			pathStack.pop();

			// set this position to visited.
			visit[s.y][s.x] = s.vIdx;

			// traverse 4 directions.
			for (int d = 0; d < 4; d++) {
				int x = s.x + directions[d][0];
				int y = s.y + directions[d][1];

				// calculate total turns of this path.
				int turn = s.turn + (s.dir == d ? 0 : 1);
				if (turn < 3) {
					// if out of range.
					if (x < 0 || x > 7 || y < 0 || y > 7) {
						continue;
					}
					// if reach destination.
					if (x == x2 && y == y2) {
						// remove matched symbols.
						board[y1][x1] = 0;
						board[y2][x2] = 0;
						return true;
					}

					// if not visited yet and is empty ( == 0).
					if ((visit[y][x] == -1 || visit[y][x] >= s.vIdx) && board[y][x] == 0) {
						// psuh the new position into stack to be the next traverse target.
						pathStack.push(state(x, y, turn, d, s.vIdx + 1));
					}
				}
			}
		}

		// cannot found a valid path or symbols are not matched, return false.
		return false;
	}
};


int main() {
	Shisensho game;

	game.ReadBoardInput();

	int x1, y1;
	int x2, y2;

	while (std::cin >> x1 >> y1 >> x2 >> y2) {
		if (game.Match(x1 + 1, y1 + 1, x2 + 1, y2 + 1)) {
			std::cout << "pair matched" << std::endl;
		}
		else {
			std::cout << "bad pair" << std::endl;
		}
	}

}

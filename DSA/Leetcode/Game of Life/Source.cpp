#include <vector>
using namespace std;

class Solution {
public:
	class Point {
	public:
		Point(int _x, int _y) :x(_x), y(_y) {}
		int x, y;
		Point operator +(const Point p2) {
			return Point(x + p2.x, y + p2.y);
		}
	};

	Point eight_direction[8] =
	{ Point(1,1),Point(1,0),Point(0,1),Point(-1,0),Point(0,-1),Point(-1,1),Point(1,-1),Point(-1,-1) };
	int get_x_pos(int old_pos, int rows) {
		if (old_pos == -1) {
			return rows - 1;
		}
		if (old_pos == rows) {
			return 0;
		}
		return old_pos;
	}
	int get_y_pos(int old_pos, int cols) {
		if (old_pos == -1) {
			return cols - 1;
		}
		if (old_pos == cols) {
			return 0;
		}
		return old_pos;
	}

	void gameOfLife(vector<vector<int>>& board) {
		if (board.size() < 3) {
			return;
		}
		vector<vector<int>> boardTmp(board);
		int rows = board.size(), cols = board[0].size();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				Point p(i, j);
				int live_state_count = 0;
				for (int k = 0; k < 8; ++k) {
					Point tmp = p + eight_direction[k];

					live_state_count += board[get_x_pos(tmp.x, rows)][get_y_pos(tmp.y, cols)];
				}
				if (board[p.x][p.y] == 1) {
					if (live_state_count < 2 || live_state_count > 3) {
						boardTmp[p.x][p.y] = 0;
					}
				}
				else {
					if (live_state_count == 3) {
						boardTmp[p.x][p.y] = 1;
					}
				}
			}
		}
		board = boardTmp;
	}
};

int main() {
	Solution s;
	return 0;
}


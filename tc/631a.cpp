#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

class TaroJiroGrid {
	public:
		bool judge(vector<string> grid) {
			for (int i = 0; i < grid.size(); i++) {
				int cnt = 1;
				for (int j = 1; j < grid.size(); j++) {
					if (grid[j][i] == grid[j - 1][i]) {
						cnt++;
					} else {
						if (cnt > grid.size() / 2) return false;
						cnt = 1;
					}
				}
				if (cnt > grid.size() / 2) return false;
			}
			return true;
		}

		bool solve(vector<string> grid, int cnt) {
			if (cnt == 0)
				if (judge(grid)) return true;
			else if (cnt == 1) {
				for (int i = 0; i < grid.size(); i++) {
					vector<string> tmp = grid;
					for (int j = 0; j < grid[i].length(); j++)
						tmp[i][j] = 'B';
					if (judge(tmp)) return true;
					tmp = grid;
					for (int j = 0; j < grid[i].length(); j++)
						tmp[i][j] = 'W';
					if (judge(tmp)) return true;
				}
			}
			return false;
		}

		int getNumber(vector<string> grid) {
			for (int i = 0; i < 2; i++) {
				if (solve(grid, i))
					return i;
			}
			return 2;
		}
};


int n;
vector<string> sb;
TaroJiroGrid gao;

int main() {
	while (cin >> n) {
		string str;
		sb.clear();
		for (int i = 0; i < n; i++) {
			cin >> str;
			sb.push_back(str);
		}
		cout << gao.getNumber(sb) << endl;
	}
	return 0;
}

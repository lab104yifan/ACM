#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 105;
const int d[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
typedef pair<int, int> pii;

int w, h, t, n;
int dp[N][N][N];
vector<pii> ans[N];

void init() {
	scanf("%d", &n);
	int ti, xa, ya, xb, yb;
	memset(dp, -1, sizeof(dp));
	while (n--) {
		scanf("%d%d%d%d%d", &ti, &xa, &ya, &xb, &yb);
		for (int i = xa; i <= xb; i++)
			for (int j = ya; j <= yb; j++)
				dp[i][j][ti] = 0;
	}
}

int dfs(int x, int y, int ti) {
	int &ans = dp[x][y][ti];
	if (ans != -1) return ans;
	ans = 0;
	if (ti == t) return ans = 1;
	for (int i = 0; i < 5; i++) {
		int xx = x + d[i][0];
		int yy = y + d[i][1];
		if (xx < 1 || xx > w || yy < 1 || yy > h) continue;
		if (dfs(xx, yy, ti + 1))
			ans = 1;
	}
	return ans;
}

int solve() {
	int flag;
	for (int i = 1; i <= t; i++) {
		ans[i].clear();
		flag = 0;
		for (int j = 1; j <= w; j++)
			for (int k = 1; k <= h; k++) {
				if (dp[j][k][i] == 1) {
					ans[i].push_back(make_pair(j, k));
					flag = 1;
				}
			}
		if (flag == 0) return 0;
	}
	flag = 1;
	for (int i = 1; i <= t; i++) {
		if (ans[i].size() == 1) {
			printf("Time step %d: The robber has been at %d,%d.\n", i, ans[i][0].first, ans[i][0].second);
			flag = 0;
		}
	}
	if (flag) return 1;
	return 2;
}

int main() {
	int cas = 0;
	while (~scanf("%d%d%d", &w, &h, &t) && w) {
		init();
		for (int i = 1; i <= w; i++)
			for (int j = 1; j <= h; j++)
				dfs(i, j, 1);
		printf("Robbery #%d:\n", ++cas);
		int tmp = solve();
		if (tmp == 0) printf("The robber has escaped.\n");
		else if (tmp == 1) printf("Nothing known.\n");
		printf("\n");
	}
	return 0;
}

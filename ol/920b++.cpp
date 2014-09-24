#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MP(a,b) make_pair(a,b)

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

typedef pair<int, int> pii;
const int N = 55;
const int INF = 0x3f3f3f3f;

int t, n, m, g[N][N], ln;
vector<int> z[N];
vector<pii> save;
vector<vector<pii> > line;
void build_line(int sx, int sy, int dx, int dy) {
	save.clear();
	while (sx < n && sy < m && sx >= 0 && sy >= 0) {
		if (g[sx][sy] == 0) return;
		save.push_back(MP(sx, sy));
		sx += dx;
		sy += dy;
	}
	line.push_back(save);
}

void build() {
	ln = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j] == 0) continue;
			for (int x = 0; i + 2 * x < n; x++) {
				for (int k = 0; k < z[x].size(); k++) {
					int y = z[x][k];
					if (j + 2 * y >= m) break;
					if (x <= i && y <= j) continue;
					build_line(i, j, x, y);
				}
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			if (g[i][j] == 0) continue;
			for (int x = 1; i - 2 * x >= 0; x++) {
				for (int k = 0; k < z[x].size(); k++) {
					int y = z[x][k];
					if (y == 0) continue;
					if (j + 2 * y >= m) break;
					if (i + x < n && y <= j) continue;
					build_line(i, j, -x, y);
				}
			}
		}
	}
}

int vis[N][N], ans, ss;

void dfs(int u, int num, int tot) {
	if (tot == ss) {
		ans = min(ans, num);
		return;
	}
	if (num >= ans) return;
	if (u == line.size()) return;
	dfs(u + 1, num, tot);
	int flag = 0;
	for (int i = 0; i < line[u].size(); i++) {
		int x = line[u][i].first;
		int y = line[u][i].second;
		vis[x][y]++;
		if (vis[x][y] > g[x][y]) {
			flag = 1;
			for (int j = i; j >= 0; j--)
				vis[line[u][j].first][line[u][j].second]--;
			break;
		}
	}
	if (flag == 0) {
		dfs(u + 1, num + 1, tot + line[u].size());
		for (int i = 0; i < line[u].size(); i++)
			vis[line[u][i].first][line[u][i].second]--;
	}
}

int main() {
	for (int i = 0; i <= 51; i++) {
		for (int j = 0; j <= 51; j++) {
			if (i == 0 && j == 0) continue;
			if (gcd(i, j) == 1) z[i].push_back(j);
		}
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		n++; m++;
		ans = INF;
		ss = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				scanf("%d", &g[i][j]);
				ss += g[i][j];
			}
		build();
		memset(vis, 0, sizeof(vis));
		dfs(0, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}

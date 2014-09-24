#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXNODE = 45;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct KM {
	int n;
	Type g[MAXNODE][MAXNODE];
	Type Lx[MAXNODE], Ly[MAXNODE], slack[MAXNODE];
	int left[MAXNODE];
	bool S[MAXNODE], T[MAXNODE];

	void init(int n) {
		this->n = n;
	}

	void add_Edge(int u, int v, Type val) {
		g[u][v] = val;
	}

	bool dfs(int i) {
		S[i] = true;
		for (int j = 0; j < n; j++) {
			if (T[j]) continue;
			Type tmp = Lx[i] + Ly[j] - g[i][j];
			if (!tmp) {
				T[j] = true;
				if (left[j] == -1 || dfs(left[j])) {
					left[j] = i;
					return true;
				}
			} else slack[j] = min(slack[j], tmp);
		}
		return false;
	}

	void update() {
		Type a = INF;
		for (int i = 0; i < n; i++)
			if (!T[i]) a = min(a, slack[i]);
		for (int i = 0; i < n; i++) {
			if (S[i]) Lx[i] -= a;
			if (T[i]) Ly[i] += a;
		}
	}

	int km() {
		for (int i = 0; i < n; i++) {
			left[i] = -1;
			Lx[i] = -INF; Ly[i] = 0;
			for (int j = 0; j < n; j++)
				Lx[i] = max(Lx[i], g[i][j]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) slack[j] = INF;
			while (1) {
				for (int j = 0; j < n; j++) S[j] = T[j] = false;
				if (dfs(i)) break;
				else update();
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans -= g[left[i]][i];
		return ans;
	}
} gao;

#define MP(a,b) make_pair(a,b)
const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

typedef pair<int, int> pii;

const int N = 45;

int t, n, m;
char g[N][N];
int idb[N][N], idx[N][N], bn, xn, vis[N][N];
pii tob[N], tox[N];

int dis(pii a, pii b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void bfs(int xs, int ys) {
	queue<pii> Q;
	Q.push(MP(xs, ys));
	memset(vis, INF, sizeof(vis));
	vis[xs][ys] = 0;
	while (!Q.empty()) {
		pii u = Q.front();
		if (g[u.first][u.second] == 'X')
			gao.add_Edge(idb[xs][ys], idx[u.first][u.second], -vis[u.first][u.second]);
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int x = u.first + d[i][0];
			int y = u.second + d[i][1];
			if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#') continue;
			if (vis[x][y] <= vis[u.first][u.second] + 1) continue;
			vis[x][y] = vis[u.first][u.second] + 1;
			Q.push(MP(x, y));
		}
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		bn = xn = 0;
		memset(gao.g, -INF, sizeof(gao.g));
		for (int i = 0; i < n; i++) {
			scanf("%s", g[i]);
			for (int j = 0; j < m; j++) {
				if (g[i][j] == 'B') {
					tob[bn] = MP(i, j);
					idb[i][j] = bn++;
				}
				if (g[i][j] == 'X') {
					tox[xn] = MP(i, j);
					idx[i][j] = xn++;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == 'B') {
					bfs(i, j);
				}
			}
		}
		gao.init(bn);
		printf("%d\n", gao.km());
	}
	return 0;
}

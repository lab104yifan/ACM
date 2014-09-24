#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 105;
const int d[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int n, m, g[N][N], sn, vis[N][N][10][35];
char str[N];

struct State {
	int x, y, k, s;
	State() {}
	State(int x, int y, int k, int s) {
		this->x = x;
		this->y = y;
		this->k = k;
		this->s = s;
	}
	int get() {
		return vis[x][y][k][s];
	}
} s, e;

bool solve() {
	queue<State> Q;
	Q.push(s);
	memset(vis, INF, sizeof(vis));
	vis[s.x][s.y][0][0] = 0;
	while (!Q.empty()) {
		State u = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			State v = u;
			int ti = u.get();
			int x = u.x + d[i][0];
			int y = u.y + d[i][1];
			if (x < 0 || x >= n || y < 0 || y >= n) continue;
			if (g[x][y] == -10) continue;
			else if (g[x][y] < 0) {
				int nu = -g[x][y] - 1;
				v.x = x; v.y = y;
				if (v.s&(1<<nu))
					ti++;
				else {
					v.s |= (1<<nu);
					ti += 2;
				}
			} else {
				v.x = x; v.y = y;
				if (g[x][y] == v.k + 1)
					v.k = g[x][y];
				ti++;
			}
			if (vis[v.x][v.y][v.k][v.s] > ti) {
				vis[v.x][v.y][v.k][v.s] = ti;
				Q.push(v);
			}
		}
	}
	int ans = INF;
	for (int i = 0; i < 32; i++)
		ans = min(vis[e.x][e.y][e.k][i], ans);
	if (ans == INF) return false;
	printf("%d\n", ans);
	return true;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		sn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			for (int j = 0; j < n; j++) {
				if (str[j] == 'K') {
					g[i][j] = 0;
					s = State(i, j, 0, 0);
				}
				if (str[j] == 'T') {
					g[i][j] = 0;
					e = State(i, j, m, 0);
				}
				if (str[j] >= '1' && str[j] <= '9')
					g[i][j] = str[j] - '0';
				if (str[j] == '#')
					g[i][j] = -10;
				if (str[j] == '.')
					g[i][j] = 0;
				if (str[j] == 'S')
					g[i][j] = (--sn);
			}
		
		}
		if (!solve()) printf("impossible\n");
	}
	return 0;
}

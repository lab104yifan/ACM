#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 505;
const int d[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};

int t, n;
int g[N][N], vis[N][N][5];

struct State {
	int x, y, t;
	State() {}
	State(int x, int y, int t) {
		this->x = x;
		this->y = y;
		this->t = t;
	}
} s, e;

int get(char c) {
	if (c == 'N') return 0;
	if (c == 'E') return 3;
	if (c == 'S') return 2;
	if (c == 'W') return 1;
	return -1;
}

const int INF = 0x3f3f3f3f;
char str[N][N];

int solve() {
	queue<State> Q;
	Q.push(s);
	memset(vis, INF, sizeof(vis));
	vis[s.x][s.y][s.t] = 0;
	while (!Q.empty()) {
		State u = Q.front();
		Q.pop();
		State v = u;
		v.t = (v.t + 1) % 4;
		if (vis[v.x][v.y][v.t] > vis[u.x][u.y][u.t] + 1) {
			vis[v.x][v.y][v.t] = vis[u.x][u.y][u.t] + 1;
			Q.push(v);
		}
		for (int i = 0; i < 4; i++) {
			State v = u;
			v.x = u.x + d[i][0];
			v.y = u.y + d[i][1];
			int add = 0;
			if (v.x < 0 || v.x >= n || v.y < 0 || v.y >= n || g[v.x][v.y] == -1) continue;
			if ((g[u.x][u.y]&(1<<u.t)) || (g[v.x][v.y]&(1<<u.t))) {
				v.t = (v.t + 3) % 4;
				add = 3;
			} else {
				v.t = (v.t + 1) % 4;
				add = 1;
			}
			if (vis[v.x][v.y][v.t] > vis[u.x][u.y][u.t] + add) {
				vis[v.x][v.y][v.t] = vis[u.x][u.y][u.t] + add;
				Q.push(v);
			}
		}
	}
	int ans = INF;
	for (int i = 0; i < 4; i++)
		ans = min(ans, vis[e.x][e.y][i]);
	if (ans == INF) ans = -1;
	return ans;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", str[i]);
		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (str[i][j] == 'M')
					s = State(i, j, 0);
				else if (str[i][j] == 'T')
					e = State(i, j, 0);
				else if (str[i][j] == '#')
					g[i][j] = -1;
				else if (str[i][j] == 'N' || str[i][j] == 'E' || str[i][j] == 'S' || str[i][j] == 'W') {
					g[i][j] = 15;
					for (int k = 0; k < 4; k++) {
						int x = i + d[k][0];
						int y = j + d[k][1];
						if (x < 0 || x >= n || y < 0 || y >= n || str[x][y] == '#') continue;
						g[x][y] |= (1<<((get(str[i][j]) + k) % 4));
					}
				}
			}
		}
		printf("Case #%d: %d\n", ++cas, solve());
	}
	return 0;
}

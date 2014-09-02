#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

const int N = 1005;

int t, n, m;
char g[N][N];
int f[N][N], vis[N][N];
typedef pair<int, int> pii;

queue<pii> Q;

void bfs1() {
	while (!Q.empty()) {
		pii u = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int x = u.first + d[i][0];
			int y = u.second + d[i][1];
			if (x < 1 || x > n || y < 1 || y > m) continue;
			if (g[x][y] == '#') continue;
			if (f[x][y] != -1) continue;
			f[x][y] = f[u.first][u.second] + 1;
			Q.push(make_pair(x, y));
		}
	}
}

pii sb;

void bfs2() {
	while (!Q.empty()) Q.pop();
	Q.push(sb);
	vis[sb.first][sb.second] = 0;
	while (!Q.empty()) {
		pii u = Q.front();
		if (u.first == 1 || u.first == n || u.second == 1 || u.second == m) {
			printf("%d\n", vis[u.first][u.second] + 1);
			return;
		}
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int x = u.first + d[i][0];
			int y = u.second + d[i][1];
			if (x < 1 || x > n || y < 1 || y > m) continue;
			if (g[x][y] == '#') continue;
			if (f[x][y] != -1 && vis[u.first][u.second] + 1 >= f[x][y]) continue;
			if (vis[x][y] != -1) continue;
			vis[x][y] = vis[u.first][u.second] + 1;
			Q.push(make_pair(x, y));
		}
	}
	printf("IMPOSSIBLE\n");
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		while(!Q.empty()) Q.pop();
		for (int i = 1; i <= n; i++) {
			scanf("%s", g[i] + 1);
			for (int j = 1; j <= m ;j++) {
				if (g[i][j] == 'F') {
					Q.push(make_pair(i, j));
					f[i][j] = 0;
				}
				else {
					if (g[i][j] == 'J')
						sb = make_pair(i, j);
					f[i][j] = -1;
				}
				vis[i][j] = -1;
			}
		}
		bfs1();
		bfs2();
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 250005;
const int MAXN = 1000005;

struct Graph {
	
	struct Edge {
		int u, v, val, next;
		Edge() {}
		Edge(int u, int v, int val = 0) {
			this->u = u;
			this->v = v;
			this->val = val;
		}
	} edge[MAXN];

	int first[N], en;

	void init() {
		memset(first, -1, sizeof(first));
		en = 0;
	}
	void add(int u, int v, int val = 0) {
		edge[en] = Edge(u, v, val);
		edge[en].next = first[u];
		first[u] = en++;
	}
} g;

const int d[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

int t, n, m, b, w, g2[505][505], match[N], vis[N];
char str[505][505];

bool dfs(int u) {
	for (int i = g.first[u]; i != -1; i = g.edge[i].next) {
		int v = g.edge[i].v;
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

bool hungary() {
	int sum = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < 2 * b; i++) {
		memset(vis, 0, sizeof(vis));
		if (!dfs(i)) return false;
	}
	return true;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		b = 0; w = 0;
		g.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", str[i]);
			for (int j = 0; j < m; j++) {
				if (str[i][j] == 'B')
					g2[i][j] = b++;
				else if (str[i][j] == 'W')
					g2[i][j] = w++;
			}
		}
		if (b * 2 != w) {
			printf("NO\n");
			continue;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (str[i][j] == 'B') {
					for (int k = 0; k < 4; k++) {
						int x = i + d[k][0];
						int y = j + d[k][1];
						if (x < 0 || x >= n || y < 0 || y >= m || str[x][y] != 'W') continue;
						if (y == j) g.add(g2[i][j] + b, g2[x][y]);
						else g.add(g2[i][j], g2[x][y]);
					}
				}
			}
		}
		if (hungary()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

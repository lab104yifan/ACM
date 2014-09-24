#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 30005;
const int MAXEDGE = 500005;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type cap, flow;
	Edge() {}
	Edge(int u, int v, Type cap, Type flow) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
	}
};

struct Dinic {
	int n, m, s, t;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool vis[MAXNODE];
	Type d[MAXNODE];
	int cur[MAXNODE];
	vector<int> cut;

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}
	void add_Edge(int u, int v, Type cap) {
		edges[m] = Edge(u, v, cap, 0);
		next[m] = first[u];
		first[u] = m++;
		edges[m] = Edge(v, u, 0, 0);
		next[m] = first[v];
		first[v] = m++;
	}

	bool bfs() {
		memset(vis, false, sizeof(vis));
		queue<int> Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = true;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (!vis[e.v] && e.cap > e.flow) {
					vis[e.v] = true;
					d[e.v] = d[u] + 1;
					Q.push(e.v);
				}
			}
		}
		return vis[t];
	}

	Type dfs(int u, Type a) {
		if (u == t || a == 0) return a;
		Type flow = 0, f;
		for (int &i = cur[u]; i != -1; i = next[i]) {
			Edge& e = edges[i];
			if (d[u] + 1 == d[e.v] && (f = dfs(e.v, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[i^1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}

	Type Maxflow(int s, int t) {
		this->s = s; this->t = t;
		Type flow = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
		}
		return flow;
	}

	void MinCut() {
		cut.clear();
		for (int i = 0; i < m; i += 2) {
			if (vis[edges[i].u] && !vis[edges[i].v])
				cut.push_back(i);
		}
	}
} gao;

#define MP(a,b) make_pair(a,b)

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

typedef pair<int, int> pii;
const int N = 55;

int t, n, m, g[N][N], ln;
vector<int> z[N];
vector<pii> save;

void build_line(int sx, int sy, int dx, int dy) {
	save.clear();
	while (sx < n && sy < m && sx >= 0 && sy >= 0) {
		if (g[sx][sy] == 0) return;
		save.push_back(MP(sx, sy));
		sx += dx;
		sy += dy;
	}
	for (int i = 0; i < save.size(); i++)
		gao.add_Edge(n * m + ln, save[i].first * n + save[i].second, 1);
	//printf("%d\n", ln);
	//for (int i = 0; i < save.size(); i++)
	//	printf("%d %d\n", save[i].first, save[i].second);
	ln++;
}

void build() {
	gao.init(0);
	ln = 1;
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
	gao.n = n * m + ln + 1;
	for (int i = 1; i < ln; i++)
		gao.add_Edge(0, n * m + i, 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			gao.add_Edge(i * n + j + 1, n * m + ln, g[i][j]);
		}
	}
}

int main() {
	for (int i = 0; i <= 50; i++) {
		for (int j = 0; j <= 50; j++) {
			if (i == 0 && j == 0) continue;
			if (gcd(i, j) == 1) z[i].push_back(j);
		}
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		n++; m++;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		build();
		printf("%d\n", gao.Maxflow(0, n * m + ln));
	}
	return 0;
}

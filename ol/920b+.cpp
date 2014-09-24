#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 105;
const int MAXEDGE = 5005 * 4;
typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type cap, flow, cost;
	Edge() {}
	Edge(int u, int v, Type cap, Type flow, Type cost) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
		this->cost = cost;
	}
};

struct MCFC {
	int n, m, s, t;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	int inq[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];
	Type a[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}

	void add_Edge(int u, int v, Type cap, Type cost) {
		printf("%d %d %d %d\n", u, v, cap, cost);
		edges[m] = Edge(u, v, cap, 0, cost);
		next[m] = first[u];
		first[u] = m++;
		edges[m] = Edge(v, u, 0, 0, -cost);
		next[m] = first[v];
		first[v] = m++;
	}

	bool bellmanford(int s, int t, Type &flow, Type &cost) {

		for (int i = 0; i < n; i++) d[i] = INF;
		memset(inq, false, sizeof(inq));
		d[s] = 0; inq[s] = true; p[s] = s; a[s] = INF;
		queue<int> Q;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (e.cap > e.flow && d[e.v] > d[u] + e.cost) {
					d[e.v] = d[u] + e.cost;
					p[e.v] = i;
					a[e.v] = min(a[u], e.cap - e.flow);
					if (!inq[e.v]) {Q.push(e.v); inq[e.v] = true;}
				}
			}
		}
		if (d[t] == INF) return false;
		flow += a[t];
		cost += d[t] * a[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].u;
		}
		return true;
	}

	Type Mincost(int s, int t) {
		Type flow = 0, cost = 0;
		while (bellmanford(s, t, flow, cost));
		return cost;
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
		gao.add_Edge(n * m + ln, save[i].first * m + save[i].second + 1, 1, 0);
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
		gao.add_Edge(0, n * m + i, INF, 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j] == 0) continue;
			gao.add_Edge(i * m + j + 1, n * m + ln, g[i][j], 0);
		}
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
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		build();
		printf("%d\n", gao.Mincost(0, n * m + ln));
	}
	return 0;
}

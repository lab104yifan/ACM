#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXNODE = 105 * 2;
const int MAXEDGE = 200005;

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

	bool Maxflow(int s, int t, int tot) {
		this->s = s; this->t = t;
		Type flow = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
		}
		return flow == tot;
	}

	void MinCut() {
		cut.clear();
		for (int i = 0; i < m; i += 2) {
			if (vis[edges[i].u] && !vis[edges[i].v])
				cut.push_back(i);
		}
	}
} gao;

const int N = 105;

int t, n;
double d;

struct Point {
	int x, y, n, m;
	void read() {
		scanf("%d%d%d%d", &x, &y, &n, &m);
	}
} p[N];

double dis(Point a, Point b) {
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrt(dx * dx * 1.0 + dy * dy);
}

int tot;

bool solve(int u) {
	gao.init(2 * n + 2);
	for (int i = 1; i <= n; i++)
		gao.add_Edge(0, i, p[i].n);
	gao.add_Edge(u + n, 2 * n + 1, tot);
	for (int i = 1; i <= n; i++) {
		if (i == u) gao.add_Edge(i, i + n, tot);
		else gao.add_Edge(i, i + n, p[i].m);
		for (int j = i + 1; j <= n; j++) {
			if (dis(p[i], p[j]) > d) continue;
			gao.add_Edge(i + n, j, tot);
			gao.add_Edge(j + n, i, tot);
		}
	}
	return gao.Maxflow(0, 2 * n + 1, tot);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%lf", &n, &d);
		tot = 0;
		for (int i = 1; i <= n; i++) {
			p[i].read();
			tot += p[i].n;
		}
		int bo = 0;
		for (int i = 1; i <= n; i++) {
			if (!solve(i)) continue;
			if (bo) printf(" ");
			else bo = 1;
			printf("%d", i - 1);
		}
		if (bo == 0) printf("-1");
		printf("\n");
	}
	return 0;
}

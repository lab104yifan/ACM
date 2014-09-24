#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 1005;
const int MAXEDGE = 1000005;

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

int n, m, p[N], t[N];
vector<int> ans[N];

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		gao.init(n + m + 2);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			ans[i].clear();
			scanf("%d", &p[i]);
			sum += p[i];
			gao.add_Edge(0, i, p[i]);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d", &t[i]);
			gao.add_Edge(n + i, n + m + 1, t[i]);
			for (int j = 1; j <= n; j++)
				gao.add_Edge(j, n + i, 1);
		}
		if (gao.Maxflow(0, n + m + 1, sum)) {
			printf("1\n");
			for (int i = 0; i < gao.m; i++) {
				if (gao.edges[i].u >= 1 && gao.edges[i].u <= n && gao.edges[i].v >= n + 1 && gao.edges[i].v <= n + m && gao.edges[i].flow == 1) {
					ans[gao.edges[i].u].push_back(gao.edges[i].v - n);
				}
			}
			for (int i = 1; i <= n; i++) {
				for (int j = 0; j < ans[i].size(); j++) {
					printf("%d%c", ans[i][j], j == ans[i].size() - 1 ? '\n' : ' ');
				}
			}
		} else printf("0\n");
	}
	return 0;
}

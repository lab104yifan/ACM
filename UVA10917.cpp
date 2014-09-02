#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f

const int MAXNODE = 1005;

struct Edge {
	int u, v, dist;
	Edge() {}
	Edge(int u, int v, int dist) {
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

struct HeapNode {
	int d, u;
	HeapNode() {}
	HeapNode(int d, int u) {
		this->d = d;
		this->u = u;
	}
	bool operator < (const HeapNode& c) const {
		return d > c.d;
	}
};

struct Dijkstra {
	int n, m;
	vector<Edge> edges;
	vector<int> g[MAXNODE];
	bool done[MAXNODE];
	int d[MAXNODE], p[MAXNODE];

	void init(int tot) {
		n = tot;
		for (int i = 0; i < n; i++)
			g[i].clear();
		edges.clear();
	}

	void add_Edge(int u, int v, int dist) {
		edges.push_back(Edge(u, v, dist));
		m = edges.size();
		g[u].push_back(m - 1);
	}

	void print(int e) {//shun xu
		if (p[e] == -1) {
			printf("%d", e + 1);
			return;
		}
		print(edges[p[e]].u);
		printf(" %d", e + 1);
	}

	void print2(int e) {//ni xu
		if (p[e] == -1) {
			printf("%d\n", e + 1);
			return;
		}
		printf("%d ", e + 1);
		print2(edges[p[e]].u);
	}

	void dijkstra(int s) {
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++) d[i] = INF;
		d[s] = 0;
		p[s] = -1;
		memset(done, false, sizeof(done));
		Q.push(HeapNode(0, s));
		while (!Q.empty()) {
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			if (done[u]) continue;
			done[u] = true;
			for (int i = 0; i < g[u].size(); i++) {
				Edge& e = edges[g[u][i]];
				if (d[e.v] > d[u] + e.dist) {
					d[e.v] = d[u] + e.dist;
					p[e.v] = g[u][i];
					Q.push(HeapNode(d[e.v], e.v));
				}
			}
		}
	}
} gao;

const int N = 1005;

int n, m, dp[N];
vector<int> g[N];
vector<Edge> save;

int dfs(int u) {
	if (dp[u] != -1) return dp[u];
	dp[u] = 0;
	if (u == 1) return dp[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		dp[u] += dfs(v);
	}
	return dp[u];
}

int main() {
	while (~scanf("%d", &n) && n) {
		gao.init(n);
		save.clear();
		for (int i = 0; i < n; i++) g[i].clear();
		scanf("%d", &m);
		int u, v, d;
		while (m--) {
			scanf("%d%d%d", &u, &v, &d);
			u--; v--;
			save.push_back(Edge(u, v, d));
			gao.add_Edge(u, v, d);
			gao.add_Edge(v, u, d);
		}
		gao.dijkstra(1);
		for (int i = 0; i < save.size(); i++) {
			int u = save[i].u, v = save[i].v;
			if (gao.d[u] > gao.d[v])
				g[u].push_back(v);
			else if (gao.d[v] > gao.d[u])
				g[v].push_back(u);
		}

		memset(dp, -1, sizeof(dp));
		printf("%d\n", dfs(0));
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f

const int MAXNODE = 505;

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
} gao1, gao2;

const int M = 2005;

int n, s, e;
Edge em[M];

int main() {
	int bo = 0;
	while (~scanf("%d%d%d", &n, &s, &e)) {
		if (bo) printf("\n");
		else bo = 1;
		gao1.init(n);
		gao2.init(n);
		s--; e--;
		int m, x, y, z;
		scanf("%d", &m);
		while (m--) {
			scanf("%d%d%d", &x, &y, &z);
			x--; y--;
			gao1.add_Edge(x, y, z);
			gao1.add_Edge(y, x, z);
			gao2.add_Edge(x, y, z);
			gao2.add_Edge(y, x, z);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &x, &y, &z);
			x--; y--;
			em[i * 2] = Edge(x, y, z);
			em[i * 2 + 1] = Edge(y, x, z);
		}
		gao1.dijkstra(s);
		gao2.dijkstra(e);
		int ans = gao1.d[e];
		int ss = e, ee = -1;
		for (int i = 0; i < 2 * m; i++) {
			int u = em[i].u, v = em[i].v, dist = em[i].dist;
			int sum = gao1.d[u] + gao2.d[v] + dist;
			if (sum < ans) {
				ans = sum;
				ss = u;
				ee = v;
			}
		}
		gao1.print(ss);
		if (ee != -1) {
			printf(" ");
			gao2.print2(ee);
		}
		else printf("\nTicket Not Used\n");
		if (ee != -1) printf("%d\n", ss + 1);
		printf("%d\n", ans);
	}
	return 0;
}
